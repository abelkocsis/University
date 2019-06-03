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
    printf("A kuldott uzenet kodja: %ld, szovege:  %s, szamai: %i, %i\n", uz.mtype, uz.mtext, uz.a, uz.b);

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
     //the starting value of random number generation
    signal(SIGUSR1, handler);

    kulcs_msg = ftok(argv[0], 2);
    //printf("A kulcs_msg: %d\n", kulcs_msg);
    uzenetsor = msgget(kulcs_msg, 0600 | IPC_CREAT);
    if (uzenetsor < 0)
    {
        perror("msgget");
        return 1;
    }


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
}

void ch(){

    srand(time(NULL));
    int r=rand()%3 + 1;
    //int r = 1;
    printf("varakozas: %i.\n", r);
    fflush(stdout);
    sleep(r);
    printf("Child: Útra kész vagyunk.\n");
    
    kuld(uzenetsor, "Csapat utra kesz!\n", 1, 2);

    fflush(stdout);
}