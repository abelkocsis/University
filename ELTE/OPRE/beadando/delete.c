#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h> 
#include <string.h>


int main()
{
    printf("\nRENDELÉS TÖRLÉSE\n\n");
    char str[80];
    long id;

    

    printf("Adja meg a törlendő megrendelés azonosítóját (id)!\n");
    gets(str);
    id = atoi(str);
    int volt = 0;

    FILE * fp1;
    FILE * fp2;

    fp1 = fopen("data.txt", "r");
    fp2 = fopen("data2.txt", "w");
    int i = 0;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp1)) != -1) {
        
        if (i % 8 == 0 && atoi(line) == id){
            int j;
            for(j = 0; j < 7; j++)
            {
                read = getline(&line, &len, fp1);
            }
            volt = 1;
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
    if (volt == 1){
        printf("Törlés végrehajtva\n");
    }
    else{
        printf("Nincs ilyen azonosítójú megrendelés.\n");
    }
    

}