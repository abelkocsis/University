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
#include <time.h>

pid_t elnok;
pid_t tag1;
pid_t tag2;
void el();
void t1();
void t2();
int args;
int pipefd[2];
int pipefd2[2];
int status;

void handler(int signumber)
{
    printf("Parent: Signal with number %i has arrived\n", signumber);
}

int main(int argc, char **argv)
//char** means an array of character arrays = array of strings
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    args = argc - 1;
    srand(time(NULL));
    if (pipe(pipefd) == -1)
    {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd2) == -1)
    {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    

    elnok = getpid();
    tag1 = fork();
    if (getpid() == elnok){
        tag2 = fork();
        if (getpid() == elnok)
            el();
        else
            t2();
    }else{
        t1();
    }
    
    if (elnok == getpid()){
        waitpid(tag1, &status, 0);
        waitpid(tag2, &status, 0);
    }


}

void el(){
    
    pause();
    //pause(); 
   
    printf("Elnok: everyone is ready\n");
    
    close(pipefd[0]);
    printf("Elnok: writing in unnamed pipe.\n");
    fflush(stdout);
    int i;
    int id [100];
    
    for (i = 0; i < args; i++){
        id[i] = rand();
        printf("%i\n", id[i]);
        fflush(stdout);

        write(pipefd[1], &id[i], sizeof(int));
        sleep(1);
    }
    close(pipefd[1]);

    printf("Elnok: kesz.\n");



}
void t1(){
    //printf("Tag1 okay\n");
    kill(elnok, SIGUSR1);
    char s[100] = "Semmi";
    close(pipefd[1]); //Usually we close the unused write end
    close(pipefd2[0]);
    printf("Ellenorzo elkezdi olvasni a csobol az adatokat!\n");
    int i = 0;
    sleep(1);
    while (read(pipefd[0], s, sizeof(s)))
    {
        printf("Ellenorzo olvasta uzenet: %ld\n", s);
        int id = atoi(s);
        fflush(stdout);
        write(pipefd2[1], &id, sizeof(int));
        printf("\n");
    }
    close(pipefd[0]);
    close(pipefd2[1]);
    printf("Ellenorzo befejezte az olvasast.\n", s);
    fflush(stdout);

}
void t2(){
    //printf("Tag2 okay\n");
    sleep(1);
    kill(elnok, SIGUSR2);

    char s[100] = "Semmi";
    close(pipefd2[1]); //Usually we close the unused write end
    printf("Lapos elkezdi olvasni a csobol az adatokat!\n");
    int i = 0;
    
    while (read(pipefd2[0], s, sizeof(s)))
    {
        printf("Lapos olvasta uzenet: %ld\n", s);
        fflush(stdout);
        printf("\n");
    }
    close(pipefd2[0]);
    printf("Lapos befejezte az olvasast.\n", s);
    fflush(stdout);
}