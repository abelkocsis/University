// ----------------------------------------------------------------------------
// Copyright 2016-2020 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------
#include "m2mobjectinstance.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#ifndef MBED_TEST_MODE
#include "mbed.h"
#include "kv_config.h"
#include "mbed-cloud-client/MbedCloudClient.h" // Required for new MbedCloudClient()
#include "factory_configurator_client.h"       // Required for fcc_* functions and FCC_* defines
#include "m2mresource.h"                       // Required for M2MResource
#include "key_config_manager.h"                // Required for kcm_factory_reset

#include "mbed-trace/mbed_trace.h"             // Required for mbed_trace_*

#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_magneto.h"


#define printReadings true

// Pointers to the resources that will be created in main_application().
static MbedCloudClient *cloud_client;
static bool cloud_client_running = true;
static NetworkInterface *network = NULL;

// Fake entropy needed for non-TRNG boards. Suitable only for demo devices.
uint8_t MBED_CLOUD_DEV_ENTROPY[] = { 0xf6, 0xd6, 0xc0, 0x09, 0x9e, 0x6e, 0xf2, 0x37, 0xdc, 0x29, 0x88, 0xf1, 0x57, 0x32, 0x7d, 0xde, 0xac, 0xb3, 0x99, 0x8c, 0xb9, 0x11, 0x35, 0x18, 0xeb, 0x48, 0x29, 0x03, 0x6a, 0x94, 0x6d, 0xe8, 0x40, 0xc0, 0x28, 0xcc, 0xe4, 0x04, 0xc3, 0x1f, 0x4b, 0xc2, 0xe0, 0x68, 0xa0, 0x93, 0xe6, 0x3a };

static M2MResource* m2m_get_res;
static M2MResource* m2m_put_res;
static M2MResource* m2m_post_res;
static M2MResource* m2m_deregister_res;
static M2MResource* m2m_factory_reset_res;
static SocketAddress sa;
static M2MResource* m2m_temp;
static M2MResource* m2m_hum;
static std::ostringstream ss;
static std::string current_readings;
static int id = 1;

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
Mutex value_increment_mutex;


struct Packet{
    int16_t magnetoDataXYZ[3] = {0};
    int16_t acceleroDataXYZ[3] = {0};
    float gyroData[3] = {0};
};

Packet p = Packet();
char *packetBytesList;
uint8_t packetBytesArray[24];

void print_client_ids(void)
{
    printf("Account ID: %s\n", cloud_client->endpoint_info()->account_id.c_str());
    printf("Endpoint name: %s\n", cloud_client->endpoint_info()->internal_endpoint_name.c_str());
    printf("Device ID: %s\n\n", cloud_client->endpoint_info()->endpoint_name.c_str());
}



void get_res_update(const char* /*object_name*/)
{
    printf("Counter resource set to %d\n", (int)m2m_get_res->get_value_int());
}

void put_res_update(const char* /*object_name*/)
{
    printf("PUT update %d\n", (int)m2m_put_res->get_value_int());
}

void execute_post(void* /*arguments*/)
{
    printf("POST executed\n");
}

void deregister_client(void)
{
    printf("Unregistering and disconnecting from the network.\n");
    cloud_client->close();
}

void deregister(void* /*arguments*/)
{
    printf("POST deregister executed\n");
    m2m_deregister_res->send_delayed_post_response();

    deregister_client();
}

void client_registered(void)
{
    printf("Client registered.\n");
    print_client_ids();
}

void client_unregistered(void)
{
    printf("Client unregistered.\n");
    (void) network->disconnect();
    cloud_client_running = false;
}

void factory_reset(void*)
{
    printf("POST factory reset executed\n");
    m2m_factory_reset_res->send_delayed_post_response();

    kcm_factory_reset();
}

void client_error(int err)
{
    printf("client_error(%d) -> %s\n", err, cloud_client->error_description());
}

void update_progress(uint32_t progress, uint32_t total)
{
    uint8_t percent = (uint8_t)((uint64_t)progress * 100 / total);
    printf("Update progress = %" PRIu8 "%%\n", percent);
}

void flush_stdin_buffer(void)
{
    FileHandle *debug_console = mbed::mbed_file_handle(STDIN_FILENO);
    while(debug_console->readable()) {
        char buffer[1];
        debug_console->read(buffer, 1);
    }
}
void update_readings(){
    BSP_MAGNETO_GetXYZ(p.magnetoDataXYZ);
    BSP_GYRO_GetXYZ(p.gyroData);
    BSP_ACCELERO_AccGetXYZ(p.acceleroDataXYZ);

    // 3333/0/1
    

    ss << std::to_string(id) << ";";
    ss << std::to_string(p.magnetoDataXYZ[0]) + "," + std::to_string(p.magnetoDataXYZ[1]) + "," + std::to_string(p.magnetoDataXYZ[2]) << ";";
    ss << p.gyroData[0] << "," << p.gyroData[1] << "," << p.gyroData[2] << ";";
    ss << std::to_string(p.acceleroDataXYZ[0]) << "," << std::to_string(p.acceleroDataXYZ[1]) << "," << std::to_string(p.acceleroDataXYZ[2]);
    ss << "|";
    

    if (id % 4 == 0){
        current_readings = std::string(ss.str());
        uint8_t buff_size = current_readings.size() + 1;
        char buffer[buff_size];
        strcpy(buffer, current_readings.c_str());
        m2m_get_res->set_value((const uint8_t *)buffer, buff_size);

        ss.str("");
        ss.clear();
    }

    id++;
}

void doPrintReadings(){
    printf("Print readings\n");
    printf("Magneto sensors: %i, %i, %i\n", p.magnetoDataXYZ[0], p.magnetoDataXYZ[1], p.magnetoDataXYZ[2]);
    printf("Gyro sensors: %f, %f, %f\n", p.gyroData[0], p.gyroData[1], p.gyroData[2]);
    printf("Accelero sensors: %i, %i, %i\n", p.acceleroDataXYZ[0], p.acceleroDataXYZ[1], p.acceleroDataXYZ[2]);
}

int main(void)
{
    // Sensor init

    BSP_MAGNETO_Init();
    BSP_ACCELERO_Init();
    BSP_GYRO_Init();

    int status;

    status = mbed_trace_init();
    if (status != 0) {
        printf("mbed_trace_init() failed with %d\n", status);
        return -1;
    }

    // Mount default kvstore
    printf("Application ready\n");
    status = kv_init_storage_config();
    if (status != MBED_SUCCESS) {
        printf("kv_init_storage_config() - failed, status %d\n", status);
        return -1;
    }

    // Connect with NetworkInterface
    printf("Connect to network\n");
    network = NetworkInterface::get_default_instance();
    if (network == NULL) {
        printf("Failed to get default NetworkInterface\n");
        return -1;
    }
    status = network->connect();
    if (status != NSAPI_ERROR_OK) {
        printf("NetworkInterface failed to connect with %d\n", status);
        return -1;
    }
    status = network->get_ip_address(&sa);
    if (status!=0) {
        printf("get_ip_address failed with %d\n", status);
        return -2;
    }
    printf("Network initialized, connected with IP %s\n\n", sa.get_ip_address());

    // Run developer flow
    printf("Start developer flow\n");
    status = fcc_init();
    if (status != FCC_STATUS_SUCCESS) {
        printf("fcc_init() failed with %d\n", status);
        return -1;
    }

    // Inject hardcoded entropy for the device. Suitable only for demo devices.
    (void) fcc_entropy_set(MBED_CLOUD_DEV_ENTROPY, sizeof(MBED_CLOUD_DEV_ENTROPY));
    status = fcc_developer_flow();
    if (status != FCC_STATUS_SUCCESS && status != FCC_STATUS_KCM_FILE_EXIST_ERROR && status != FCC_STATUS_CA_ERROR) {
        printf("fcc_developer_flow() failed with %d\n", status);
        return -1;
    }

    printf("Create resources\n");
    M2MObjectList m2m_obj_list;

//Create GET resource 3333/0/1 for sensor readings

    m2m_get_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 3333, 0, 1, M2MResourceInstance::STRING, M2MBase::GET_ALLOWED);

    // POST resource 5000/0/1 to trigger deregister.
    m2m_deregister_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 5000, 0, 1, M2MResourceInstance::INTEGER, M2MBase::POST_ALLOWED);


    // Use delayed response
   

    if (m2m_deregister_res->set_execute_function(deregister) != true) {
        printf("m2m_post_res->set_execute_function() failed\n");
        return -1;
    }

    // optional Device resource for running factory reset for the device. Path of this resource will be: 3/0/5.


    printf("Register Pelion Device Management Client\n\n");

#ifdef MBED_CLOUD_CLIENT_SUPPORT_UPDATE
    cloud_client = new MbedCloudClient(client_registered, client_unregistered, client_error, NULL, update_progress);
#else
    cloud_client = new MbedCloudClient(client_registered, client_unregistered, client_error);
#endif // MBED_CLOUD_CLIENT_SUPPORT_UPDATE

    cloud_client->add_objects(m2m_obj_list);
    cloud_client->setup(network);

    t.start(callback(&queue, &EventQueue::dispatch_forever));
    // 185
    queue.call_every(40, update_readings);
    if (printReadings){
        queue.call_every(3000, doPrintReadings);
    }

    // Flush the stdin buffer before reading from it
    flush_stdin_buffer();

    while(cloud_client_running) {
        int in_char = getchar();
        if (in_char == 'i') {
            print_client_ids(); // When 'i' is pressed, print endpoint info
            continue;
        } else if (in_char == 'r') {
            (void) fcc_storage_delete(); // When 'r' is pressed, erase storage and reboot the board.
            printf("Storage erased, rebooting the device.\n\n");
            ThisThread::sleep_for(1*1000);
            NVIC_SystemReset();
        } else if (in_char > 0 && in_char != 0x03) { // Ctrl+C is 0x03 in Mbed OS and Linux returns negative number
            update_readings(); // Simulate button press
            continue;
        }
        deregister_client();
        break;
    }
    return 0;
}

#endif /* MBED_TEST_MODE */
