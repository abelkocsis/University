#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h> 


int main()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    printf("\nA beérkezett rendelések adatai:\n\n");

    int i = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        switch (i % 8)
        {
            case 1:
                printf("Rendelés azonosítója: ");
                break;
            case 2:
                printf("Lakcím: ");
                break;
            case 3:
                printf("Négyzetméter: ");
                break;
            case 4:
                printf("Részmunka azonosítója: ");
                break;
            case 5:
                printf("Részmunka megnevezése: ");
                break;
            case 6:
                printf("Határidő év: ");
                break;
            case 7:
                printf("Határidő hónap: ");
                break;
            case 0:
                printf("Határidő nap: ");
                break;
            default:
                break;
        }
        
        printf("%s", line);
        if (i % 8 == 0){
            printf("\n");
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}