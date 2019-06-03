#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h> 
#include <time.h>
#include <unistd.h> 
#include <wait.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h> 
#include<string.h>

void handler(int signumber){
  printf("Signal with number %i has arrived\n",signumber);
}

typedef struct {
    long mtype;
    char mtext [1024];
}message;

int kuldok(int uzenetsor){
    //printf("send...\n");
    const message uz = {5, "1"};
    int status;
    status = msgsnd( uzenetsor, &uz, strlen ( uz.mtext ) + 1 , 0 ); 
    if ( status < 0 ) 
        printf("error: mdgsnd"); 
        
    
    return 0;
}

int kuldbad(int uzenetsor){
    //printf("send...\n");
    const message uz = {5, "0"};
    int status;
    status = msgsnd( uzenetsor, &uz, strlen ( uz.mtext ) + 1 , 0 ); 
    if ( status < 0 ) 
        printf("error: mdgsnd"); 
        
    
    return 0;
}
char rendelesId [15];
char reszmunkaAzon [15];
pid_t child;

void deleteReszmunka();

int fogad (int uzenetsor){
    //printf("receive...\n");
    message uz; 
    int status; 
    status = msgrcv(uzenetsor, &uz, 1024, 5, 0 ); 
    if ( status < 0 ) 
        printf("error: msgsnd"); 
    else{
        int i = atoi(uz.mtext);
        //printf( "A kapott uzenet kodja: %ld, szovege:  %i\n", uz.mtype, i ); 
        if (i == 1){
            printf("A csapatnak sikerült a munka elvégzése.");
            deleteReszmunka();
        }
        else{
            printf("A csapatnak nem sikerült a munka elvégzése.");
        }
    }
       
    waitpid(child,&status,0); 
    return 0; 
}

pid_t parent;

void varLak();
void renovTeam();
int pipefd[2]; // unnamed pipe file descriptor array
char sz[100];  // char array for reading from pipe
int uzenetsor;
key_t kulcs;
int status;

int main(int argc, char* argv[])
{
    
    
    kulcs = ftok(argv[0],1); 
    uzenetsor = msgget( kulcs, 0600 | IPC_CREAT ); 
    if ( uzenetsor < 0 ) { 
        printf("error: msgget"); 
        return 1; 
    } 
    
    char str[80];
    
    parent = getpid();
    char * args[20];
    int going = 1;

    signal(SIGUSR1,handler);
    signal(SIGUSR2,handler);
    
    if (pipe(pipefd) == -1) {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    child = fork();
    if ((getpid() == parent)){
        varLak();
    }
    else{
        renovTeam();
    }
    //printf("One finished");

}

void varLak(){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    //printf("\nA beérkezett rendelések adatai:\n\n");

    char atmRendelesId [15];
    char atmRendelesCim [30];
    char atmRendelesMeret [10];
    char atmReszmunkaAzon [15];
    char atmReszmunkaMegnevezes[30];
    char atmReszmunkaEv [10];
    char atmReszmunkaHonap[10];
    char atmReszmunkaNap[10];

    char rendelesCim [30];
    char rendelesMeret [10];
    char reszmunkaMegnevezes[30];
    char reszmunkaEv [10] = "9999";
    char reszmunkaHonap[10];
    char reszmunkaNap[10];

    int i = 1;
    int c = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        c++;
        switch (i % 8)
        {
            case 1:
                memcpy(atmRendelesId , line, 15);
                break;
            case 2:
                memcpy(atmRendelesCim , line, 30);
                break;
            case 3:
                memcpy(atmRendelesMeret , line, 10);
                break;
            case 4:
                memcpy(atmReszmunkaAzon , line, 15);
                break;
            case 5:
                memcpy(atmReszmunkaMegnevezes , line, 30);
                break;
            case 6:
                memcpy(atmReszmunkaEv , line, 10);
                break;
            case 7:
                memcpy(atmReszmunkaHonap , line, 10);
                break;
            case 0:
                memcpy(atmReszmunkaNap , line, 10);
                break;
            default:
                break;
        }
        
        if (i % 8 == 0){
            if (atoi(atmReszmunkaEv) < atoi(reszmunkaEv) || 
                (atoi(atmReszmunkaEv) == atoi(reszmunkaEv) &&
                atoi(atmReszmunkaHonap) < atoi(reszmunkaHonap)) ||
                (
                    atoi(atmReszmunkaEv) == atoi(reszmunkaEv) &&
                    atoi(atmReszmunkaHonap) == atoi(reszmunkaHonap) &&
                    atoi(atmReszmunkaNap) < atoi(reszmunkaNap)
                )
        
            ){
                strncpy(rendelesId, atmRendelesId, 15);
                strncpy(rendelesCim, atmRendelesCim, 30);
                strncpy(rendelesMeret, atmRendelesMeret, 10);
                strncpy(reszmunkaAzon, atmReszmunkaAzon, 15);
                strncpy(reszmunkaMegnevezes, atmReszmunkaMegnevezes, 30);
                strncpy(reszmunkaEv, atmReszmunkaEv, 10);
                strncpy(reszmunkaHonap, atmReszmunkaHonap, 10);
                strncpy(reszmunkaNap, atmReszmunkaNap, 10);
            }
            //printf(atmReszmunkaAzon);
            //printf(reszmunkaAzon);
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    
    if (c == 0){
        printf("Nincs elvégezhető munka.\n");
        kill(child, SIGKILL);
    }else{
        pause();

        printf("VarazsLak elkezdte az adatok elkuldeset.\n");
        close(pipefd[0]); //Usually we close unused read end
    
        write(pipefd[1], rendelesId,15);
        sleep(1);
        write(pipefd[1], rendelesCim,30);
        sleep(1);
        write(pipefd[1], rendelesMeret,10);
        sleep(1);
        write(pipefd[1], reszmunkaAzon,15);
        sleep(1);
        write(pipefd[1], reszmunkaMegnevezes,30);
        sleep(1);
        write(pipefd[1], reszmunkaEv,10);
        sleep(1);
        write(pipefd[1], reszmunkaHonap,10);
        sleep(1);
        write(pipefd[1], reszmunkaNap,10);
    
    //close(pipefd[1]); // Closing write descriptor    
    //fflush(NULL); 	// flushes all write buffers (not necessary)
    
        pause();
        sleep(1);
        fogad( uzenetsor ); 
    
    
        printf("VarazsLak finished\n");
    }

    

}
void renovTeam(){
    
    char rendelesCim [30];
    char rendelesMeret [10];
    char reszmunkaAzon [15];
    char reszmunkaMegnevezes[30];
    char reszmunkaEv [10] = "9999";
    char reszmunkaHonap[10];
    char reszmunkaNap[10];

    sleep(1);
    printf("Renovation team is ready.");
    kill(parent, SIGUSR1);

    printf("RenovTeam elkezdi olvasni az adatokat!\n");
    read(pipefd[0],rendelesId,15); 
    sleep(1);
    read(pipefd[0],rendelesCim,30); 
    sleep(1);
    read(pipefd[0],rendelesMeret,10);
    sleep(1);
    read(pipefd[0],reszmunkaAzon,15);
    sleep(1);
    read(pipefd[0],reszmunkaMegnevezes,30);
    sleep(1);
    read(pipefd[0],reszmunkaEv,10);
    sleep(1);
    read(pipefd[0],reszmunkaHonap,10);
    sleep(1);
    read(pipefd[0],reszmunkaNap,10);
    
    printf("RenovTeam fogadta a következő adatokat:\n");
    printf("Rendelés azonosító: %s\n", rendelesId);
    printf("Cím: %s\n", rendelesCim);
    printf("Lakás méret: %s\n", rendelesMeret);
    printf("Részmunka azonosító: %s\n", reszmunkaAzon);
    printf("Részmunka megnevezés: %s\n", reszmunkaMegnevezes);
    printf("Részmunka határidő: %s %s %s\n", reszmunkaEv, reszmunkaHonap, reszmunkaNap);


    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand();
    int siker;
    if (r % 100 > 10){
        printf("RenovTeam: We did it.\n");
        siker = 1;
    }
    else{
        siker = 0;
        printf("RenovTeam: We failed to do it.\n");
    }
    
	printf("\n");
    close(pipefd[0]); // finally we close the used read end
    
    kill(parent, SIGUSR2);
    if (siker == 1){
        kuldok( uzenetsor );
    }
    else{
        kuldbad( uzenetsor );
    }
    sleep(3);
    status = msgctl( uzenetsor, IPC_RMID, NULL ); 
    if ( status < 0 ) 
        printf("msgctl error"); 

    printf("RenovTeam finished.\n");

}

void deleteReszmunka(){
    //printf("deleteReszmunka started\n");

    char* rid = &rendelesId[0];
    char* reszazon = &reszmunkaAzon[0];
    int rendelesId = atoi(rid);
    int reszmunkaAzon = atoi(reszazon);
    //printf("torlendo rendelesId: %i\n torlendo reszmunkaazon: %i\n", rendelesId, reszmunkaAzon);
    FILE * fp1;
    FILE * fp2;

    fp1 = fopen("data.txt", "r");
    fp2 = fopen("data2.txt", "w");

    int i = 0;

    char * line = NULL;
    char * line2 = NULL;
    char * line3 = NULL;
    char * lineRmAz = NULL;
    size_t len = 0;
    ssize_t read;
    int j;
    int ok = 0;

    while ((read = getline(&line, &len, fp1)) != -1) {
        
        if (i % 8 == 0 && atoi(line) == rendelesId){
            getline(&line2, &len, fp1);
            getline(&line3, &len, fp1);
            getline(&lineRmAz, &len, fp1);
            
            if (atoi(lineRmAz) == reszmunkaAzon){
                ok = 1;
                for(j= 0; j < 4; j++)
                {
                    
                    getline(&line, &len, fp1);
                }
                
            }
            else{
                fprintf(fp2, "%s", line);
                fprintf(fp2, "%s", line2);
                fprintf(fp2, "%s", line3);
                fprintf(fp2, "%s", lineRmAz);
                for (j = 0; j < 4; j++)
                {
                read = getline(&line, &len, fp1);
                fprintf(fp2, "%s", line);
                }
            }
        }
        else{
            fprintf(fp2, "%s", line);

            int j;
            for (j = 0; j < 7; j++)
            {
                read = getline(&line, &len, fp1);
                fprintf(fp2, "%s", line);
            }
        }
        i += 8;
        
    }
    fclose(fp1);
    fclose(fp2);
    remove("data.txt");
    rename("data2.txt", "data.txt");
    if (ok){
        printf("A végrehajtott részmunka törölve.\n");
    }
    else{
        printf("A végrehajtott részmunka nem lett törölve.\n");
    }

}