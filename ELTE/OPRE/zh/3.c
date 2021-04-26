#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>

pid_t parent;
pid_t child;
void par();
void ch();
int status;
int uzenetsor;
key_t kulcs_msg;
int pid, fd, fid;
key_t kulcs_om;
int oszt_mem_id;
char *osztot_mem_s;

void handler(int signumber)
{
    if (getpid() == parent)
        printf("Parent: Signal with number %i has arrived\n", signumber);
    else
    {
        printf("Child: Riszatas erkezett\n");
    }
}

struct uzenet
{
    long mtype; //ez egy szabadon hasznalhato ertek, pl uzenetek osztalyozasara
    char mtext[100];
    long a;
    long b;
};

int kuld(int uzenetsor, char uzenetmsg[100], long a, long b)
{
    struct uzenet uz2 = {5, uzenetmsg, 5, 5};
    strncpy(uz2.mtext, uzenetmsg, 101);
    uz2.a = a;
    uz2.b = b;
    const struct uzenet uz = uz2;
    int status;
    //printf("A kuldott uzenet kodja: %ld, szovege:  %s, szamai: %i, %i\n", uz.mtype, uz.mtext, uz.a, uz.b);

    status = msgsnd(uzenetsor, &uz, sizeof(uz.mtext) + 2 * sizeof(long), 0);
    // a 3. param ilyen is lehet: sizeof(uz.mtext)
    // a 4. parameter gyakran IPC_NOWAIT, ez a 0-val azonos
    if (status < 0)
        perror("msgsnd");
    return 0;
}

int fogad(int uzenetsor)
{
    struct uzenet uz;
    int status;
    // az utolso parameter(0) az uzenet azonositoszama
    // ha az 0, akkor a sor elso uzenetet vesszuk ki
    // ha >0 (5), akkor az 5-os uzenetekbol a kovetkezot
    // vesszuk ki a sorbol
    status = msgrcv(uzenetsor, &uz, sizeof(char) * 101 + 2 * sizeof(long), 5, 0);

    if (status < 0)
        perror("msgsnd");
    else
        printf("%s", uz.mtext);
    return 0;
}

int main(int argc, char **argv)
//char** means an array of character arrays = array of strings
{
    srand(time(NULL));
     //the starting value of random number generation
    signal(SIGUSR1, handler);

    kulcs_msg = ftok(argv[0], 0);
    //printf("A kulcs_msg: %d\n", kulcs_msg);
    uzenetsor = msgget(kulcs_msg, 0600 | IPC_CREAT);
    if (uzenetsor < 0)
    {
        perror("msgget");
        return 1;
    }
    remove("fifo.ftc");
    fid = mkfifo("fifo.ftc", S_IRUSR | S_IWUSR); // creating named pipe file
    if (fid == -1)
    {
        printf("Error number: %i", errno);
        exit(EXIT_FAILURE);
    }

    kulcs_om = ftok(argv[0], 3);
    oszt_mem_id = shmget(kulcs_om, 500, IPC_CREAT | S_IRUSR | S_IWUSR);
    osztot_mem_s = (char *)shmat(oszt_mem_id, (void *)0x5000000, 0);
    printf("Shared memory segment ID is %d\n", oszt_mem_id);



    parent = getpid();
    child = fork();
    if (parent == getpid()){
        par();
    }
    else{
        ch();
    }

    if (getpid() == parent)
    {
        waitpid(child, &status, 0);
        printf("Parent finished.\n");
    }
    else
    {
        printf("Children finished.\n");
    }
    fflush(stdout);
    return 0;
}

void par(){
    kill(child, SIGUSR1);
    fogad(uzenetsor);

    char a = rand() % 100;
    char b = rand() % 100;
    //printf("Befora printf\n");
    fflush(stdout);
    printf("Parent pid: %d\n Coords: %i, %i\n", getpid(), a, b);
    //printf("After printf\n");
    fflush(stdout);
    char s[100] = {a, b, '\0'};
    //printf("Gyerek vagyok, irok a csobe!\n");
    //printf("Csonyitas eredmenye: %d!\n", fid);
    fd = open("fifo.ftc", O_WRONLY);
    //printf("writing start...!\n");
    fflush(stdout);

    write(fd, s, 100);
    close(fd);
    //printf("Gyerek vagyok, beirtam, vegeztem!\n");
    printf("\n");

    //printf("Sleep started in Szulo\n");
    sleep(2);
    //printf("Szülő: Indulna a szemafor down!\n");
    //szemafor_muvelet(semid, -1); // down, wait if necessary
    //printf("Szülő: Elindult a szemafor down!\n");
    printf("A szülő ezt olvasta az osztott memoriabol: %s\n", osztot_mem_s);
    //szemafor_muvelet(semid, 1); // up
    // szulo is elengedi
    shmdt(osztot_mem_s);
}

void ch(){

    
    int r=rand()%3 + 1;
    //int r = 1;
    printf("varakozas: %i.\n", r);
    fflush(stdout);
    sleep(r);
    printf("Child: Útra kész vagyunk.\n");
    
    kuld(uzenetsor, "Csapat utra kesz!\n", 1, 2);

    fflush(stdout);
    sleep(1);
    char s[1024] = "Semmi";
    fd = open("fifo.ftc", O_RDONLY);
    printf("Reading start\n");
    fflush(stdout);
    read(fd, s, sizeof(s));
    //printf("Ezt olvastam a csobol: %i , %i\n", s[0], s[1]);
    printf("Child pid: %d\n Coords: %i, %i\n", getpid(), s[0], s[1]);

    close(fd);

    printf("Elfoglaljuk a területet...\n");
    sleep(1);

   //OSZTOTT MEM
    //printf("Osztott memoria start\n");
    fflush(stdout);
    char buff[] = "X Y GPS Koordinataju akacos elfoglalva!";
    // beirunk a memoriaba
    printf("Buffer letrehozva.\n");
    //strcpy(osztot_mem_s, buff);

    sprintf(osztot_mem_s, buff);
    printf("Gyerek irt az osztott memoriaba.\n");

    sleep(4);
    printf("Gyerek, szemafor up!\n");
    //szemafor_muvelet(semid, 1); // Up

    // elengedjuk az osztott memoriat
    shmdt(osztot_mem_s);
    printf("Gyerek elengedte az osztott memoriat.\n");
    sleep(1);
    shmctl(oszt_mem_id, IPC_RMID, NULL);
}