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

#define MEMSIZE 1024

pid_t parent;
pid_t child;
int pid, fd, fid;
int pipefd[2];
int uzenetsor, status;
key_t kulcs_msg;
key_t kulcs_om;
int oszt_mem_id;
char *osztot_mem_s;
key_t kulcs_szemafor;
int sh_mem_id, semid;
char *s_szemafor;

//TODO in ZH: ne felejtsem el a signal (SIGUSR1-et atirni, ha kell)

void par();
void ch();

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
        printf("A kapott uzenet kodja: %ld, szovege:  %s, szamai: %i, %i\n", uz.mtype, uz.mtext, uz.a, uz.b);
    return 0;
}

void handler(int signumber)
{
    if (getpid() == parent)
        printf("Parent: Signal with number %i has arrived\n", signumber);
    else
    {
        printf("Child: Signal with number %i has arrived\n", signumber);
    }
}

int szemafor_letrehozas(const char *pathname, int szemafor_ertek)
{
    int semid;
    key_t kulcs;

    kulcs = ftok(pathname, 1);
    if ((semid = semget(kulcs, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) < 0)
        perror("semget");
    // semget 2. parameter is the number of semaphores
    if (semctl(semid, 0, SETVAL, szemafor_ertek) < 0) //0= first semaphores
        perror("semctl");

    return semid;
}

void szemafor_muvelet(int semid, int op)
{
    struct sembuf muvelet;

    muvelet.sem_num = 0;
    muvelet.sem_op = op; // op=1 up, op=-1 down
    muvelet.sem_flg = 0;

    if (semop(semid, &muvelet, 1) < 0) // 1 number of sem. operations
        perror("semop");
}

void szemafor_torles(int semid)
{
    semctl(semid, 0, IPC_RMID);
}

int main(int argc, char **argv)
//char** means an array of character arrays = array of strings
{

    //SIGNAL
    signal(SIGUSR1, handler); //handler = SIG_IGN; //- ignore the signal (not SIGKILL,SIGSTOP),
                              //handler = SIG_DFL - back to default behavior
    int status;
    printf("Program: %s\n", argv[0]);

    int i;
    printf("Number of command line arguments are: %i\n", argc);
    for (i = 1; i < argc; i++)
    {
        printf("%i. argument is (%i)\n", i, atoi(argv[i]) + 1);
    }

    //NEVCSO

    printf("Fifo start!\n");
    remove("fifo.ftc");
    fid = mkfifo("fifo.ftc", S_IRUSR | S_IWUSR); // creating named pipe file
    if (fid == -1)
    {
        printf("Error number: %i", errno);
        exit(EXIT_FAILURE);
    }
    printf("Mkfifo vege, fork indul!\n");

    //PIPE, UNNAMED
    if (pipe(pipefd) == -1)
    {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }

    //ÜZENET
    kulcs_msg = ftok(argv[0], 2);
    printf("A kulcs_msg: %d\n", kulcs_msg);
    uzenetsor = msgget(kulcs_msg, 0600 | IPC_CREAT);
    if (uzenetsor < 0)
    {
        perror("msgget");
        return 1;
    }

    //OSZTOTTMEM
    kulcs_om = ftok(argv[0], 3);
    oszt_mem_id = shmget(kulcs_om, 500, IPC_CREAT | S_IRUSR | S_IWUSR);
    osztot_mem_s = (char *)shmat(oszt_mem_id, (void *)0x5000000, 0);
    printf("Shared memory segment ID is %d\n", oszt_mem_id);

    //SZEMAFOROS OSZTOTTMEM
    kulcs_szemafor = ftok(argv[0], 1);
    sh_mem_id = shmget(kulcs_szemafor, MEMSIZE, IPC_CREAT | S_IRUSR | S_IWUSR);
    s_szemafor = (char *)shmat(sh_mem_id, (void *)0x5000000, 0);
    semid = szemafor_letrehozas(argv[0], 0); // sem state is down!!!

    //FORK
    parent = getpid();
    child = fork();
    if (getpid() == parent)
    {
        par();
    }
    else
    {
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

void par()
{
    printf("Parent started\n");
    srand(time(NULL));    //the starting value of random number generation
    int r = rand() % 100; //number between 0-99
    printf("Random number %i\n", r);
    printf("\n\n");

    //SIGNAL
    printf("Par: Waiting for signal...\n");
    pause();
    printf("Par:pause ended\n");

    sleep(2);
    kill(child, SIGUSR1);
    printf("\n\n");
    //NEVCSO
    //READ
    char s[1024] = "Semmi";
    printf("Csonyitas eredmenye szuloben: %d!\n", fid);
    fd = open("fifo.ftc", O_RDONLY);
    read(fd, s, sizeof(s));
    printf("Parent: Ezt olvastam a csobol: %s \n", s);
    close(fd);
    printf("\n");
    //WRITE
    printf("Parent vagyok, irok a csobe!\n");
    printf("Csonyitas eredmenye: %d!\n", fid);
    fd = open("fifo.ftc", O_WRONLY);
    write(fd, "Hajra Ujpest!\n", 12);
    close(fd);
    printf("Parent vagyok, beirtam, vegeztem!\n");
    printf("\n");

    //POLL, UNNAMED,
    //WRITE
    sleep(2);
    srand(time(NULL));
    r = rand();
    r = r % 10 + 5;
    int i = 0;
    printf("%i", r);
    close(pipefd[0]);
    printf("Parent: writing in unnamed pipe.\n");
    write(pipefd[1], "valami", 7);
    sleep(1);
    write(pipefd[1], "valami2", 8);
    sleep(1);
    write(pipefd[1], "valami3", 8);
    sleep(1);
    close(pipefd[1]); // Closing write descriptor
    //fflush(NULL);
    printf("Szulo beirta az adatokat a csobe!\n");

    printf("\n\n");
    //UZENETSOR
    fogad(uzenetsor);

    //OSZTOTT MEMÓRIA
    //READ
    kill(child, SIGUSR1);
    printf("Sleep started in Szulo\n");
    sleep(1);
    printf("Szülő: Indulna a szemafor down!\n");
    szemafor_muvelet(semid, -1); // down, wait if necessary
    printf("Szülő: Elindult a szemafor down!\n");
    printf("A szülő ezt olvasta az osztott memoriabol: %s\n", osztot_mem_s);
    szemafor_muvelet(semid, 1); // up
    // szulo is elengedi
    shmdt(osztot_mem_s);

    printf("\n\n");
}
void ch()
{
    //SIGNAL
    printf("Child started\n");
    printf("Child sending signal..\n");
    sleep(1);
    kill(parent, SIGUSR1);
    printf("Child: signal sended\n");

    printf("Child: Waiting for signal...\n");
    pause();
    printf("Child: pause ended\n");
    printf("\n\n");

    //NEVCSO
    //WRITE
    char s[100] = "Semmi";
    printf("Gyerek vagyok, irok a csobe!\n");
    printf("Csonyitas eredmenye: %d!\n", fid);
    fd = open("fifo.ftc", O_WRONLY);
    write(fd, "Hajra Fradi!\n", 12);
    close(fd);
    printf("Gyerek vagyok, beirtam, vegeztem!\n");
    printf("\n");

    //READ
    printf("Csonyitas eredmenye gyerekben: %d!\n", fid);
    fd = open("fifo.ftc", O_RDONLY);
    read(fd, s, sizeof(s));
    printf("Ezt olvastam a csobol: %s \n", s);
    close(fd);

    //PIPE UNNAMED
    //READ
    close(pipefd[1]); //Usually we close the unused write end
    printf("Gyerek elkezdi olvasni a csobol az adatokat!\n");
    int i = 0;
    while (read(pipefd[0], s, sizeof(s)))
    {
        printf("Gyerek olvasta uzenet: %s", s);
        printf("\n");
    }
    close(pipefd[0]); // finally we close the used read end
    printf("Gyerek befejezte a nevtelen pipe olvasasat\n");

    printf("\n\n");

    //ÜZENETSOR
    //WRITE

    kuld(uzenetsor, "asd", 1, 2); // Parent sends a message.
                                  //itt biztosítani kell, hogy elolvassa a másik, mielőtt töröljük
    //status = msgctl(uzenetsor, IPC_RMID, NULL);

    printf("\nuzenetsor vege\n");

    //OSZTOTT MEMORIA
    //WRITE
    pause();
    printf("Osztott memoria start\n");
    fflush(stdout);
    char buff[] = "Hajra a faszom! \n\n";
    // beirunk a memoriaba
    printf("Buffer letrehozva.\n");
    //strcpy(osztot_mem_s, buff);

    sprintf(osztot_mem_s, buff);
    printf("Gyerek irt az osztott memoriaba.\n");

    sleep(4);
    printf("Gyerek, szemafor up!\n");
    szemafor_muvelet(semid, 1); // Up

    // elengedjuk az osztott memoriat
    shmdt(osztot_mem_s);
    printf("Gyerek elengedte az osztott memoriat.\n");
    sleep(1);
    shmctl(oszt_mem_id, IPC_RMID, NULL);

    printf("\n\n");
}