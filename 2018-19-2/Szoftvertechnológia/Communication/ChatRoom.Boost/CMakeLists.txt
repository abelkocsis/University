cmake_minimum_required(VERSION 3.5)
project(chat)

set(CMAKE_CXX_STANDARD 11)
if(MSVC)
  # Exception Handling Model for MSVC 
  set(CMAKE_CXX_FLAGS "/EHsc")
else()
  set(CMAKE_CXX_FLAGS "-O2 -pedantic -Wall")
endif()

# Boost
find_package(Boost 1.60 REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(server
    server.cpp
    chat_message.hpp)
target_link_libraries(server ${Boost_LIBRARIES})

add_executable(client
    client.cpp
    chat_message.hpp)
target_link_libraries(client ${Boost_LIBRARIES})
