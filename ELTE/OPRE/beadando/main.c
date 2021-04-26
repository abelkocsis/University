#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h> 
#include <string.h> 

int main()
{
    printf("\nVarázs-Lak Kft\n");

    int status;
    char str[80];
    
    pid_t child;
    pid_t parent = getpid();
    char ** args[20];
    int going = 1;

    

    

    while (going == 1){

    printf("\nAdja meg az alábbi műveletek egyikét!\n");
    printf("P : Beérkezett rendelések kilistázása\n");
    printf("A : Új rendelés felvétele\n");
    printf("D : Rendelés törlése\n");
    printf("E : Rendelés módosítása\n");
    printf("S : Munka elvégzésének szimulációjának indítása\n");
    printf("Q : Kilépés\n");


    gets(str);
    switch (str[0])
    {
        case 'P':
            child = fork();
            args[0] = "print";
            if (!(getpid() == parent)){
                execv("print", args);
            }
            break;
        case 'A':
            child = fork();
            args[0] = "add";
            if (!(getpid() == parent)){
                execv("add", args);
            }
            break;
        case 'D':
            child = fork();
            args[0] = "delete";
            if (!(getpid() == parent)){
                execv("delete", args);
            }
            break;
        case 'E':
            child = fork();
            args[0] = "edit";
            if (!(getpid() == parent)){
                execv("edit", args);
            }
            break;
        case 'S':
            child = fork();
            args[0] = "simulation";
            if (!(getpid() == parent)){
                execv("simulation", args);
            }
            break;
        case 'Q':
            going = 0;
            break;
        default:
            printf("Érvénytelen művelet!\n");
            break;
        
    }
    waitpid(child,&status,0); 
    //sleep(3);
    }


    

}