#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define MEMSIZE 1024

int szemafor_letrehozas(const char* pathname,int szemafor_ertek){
    int semid;
    key_t kulcs_szemafor;
    
    kulcs_szemafor=ftok(pathname,1);    
    if((semid=semget(kulcs_szemafor,1,IPC_CREAT|S_IRUSR|S_IWUSR ))<0)
	perror("semget");
    // semget 2. parameter is the number of semaphores   
    if(semctl(semid,0,SETVAL,szemafor_ertek)<0)    //0= first semaphores
        perror("semctl");
       
    return semid;
}


void szemafor_muvelet(int semid, int op){
    struct sembuf muvelet;
    
    muvelet.sem_num = 0;
    muvelet.sem_op  = op; // op=1 up, op=-1 down 
    muvelet.sem_flg = 0;
    
    if(semop(semid,&muvelet,1)<0) // 1 number of sem. operations
        perror("semop");	    
}

void szemafor_torles(int semid){
      semctl(semid,0,IPC_RMID);
}

int main (int argc,char* argv[]) {

    pid_t child;
    key_t kulcs_szemafor;
    int sh_mem_id,semid;
    char *s_szemafor;

    kulcs_szemafor=ftok(argv[0],1);
    sh_mem_id=shmget(kulcs_szemafor,MEMSIZE,IPC_CREAT|S_IRUSR|S_IWUSR);
    s_szemafor = shmat(sh_mem_id,NULL,0);
//
    semid = szemafor_letrehozas(argv[0],0); // sem state is down!!!
//
    child = fork();
    if(child>0){    
    
       char buffer[] = "I like Illes (Pop group:)!\n";
	printf("Szulo indul, kozos memoriaba irja: %s\n",buffer);
       sleep(4);            // child waits during sleep
       strcpy(s_szemafor,buffer);
	printf("Szulo, szemafor up!\n");
       szemafor_muvelet(semid,1); // Up
       shmdt(s_szemafor);	// release shared memory
       wait(NULL);       
       szemafor_torles(semid);
	shmctl(sh_mem_id,IPC_RMID,NULL);
    } else if ( child == 0 ) {	
    
       // critical section
	printf("Gyerek: Indula szemafor down!\n");
       szemafor_muvelet(semid,-1); // down, wait if necessary
       printf("Gyerek, down rendben, eredmeny: %s",s_szemafor);  
       szemafor_muvelet(semid,1); // up      
       // end of critical section  
       shmdt(s_szemafor);
    }

   return 0;
}


