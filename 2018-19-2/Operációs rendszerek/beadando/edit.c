#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h>
#include <string.h>

void cimVagyMeretModosit(int id, int cim);
void reszmunkamodosit(int id);

char str[80];

int main()
{
    printf("\nMEGRENDELÉS SZERKESZTÉSE\n\n");
    char reszmunkanev[80];
    long id;

    printf("Adja meg a módisítani kívánt rendelés azonosítóját (id)!\n");
    gets(str);
    id = atoi(str);

    int ok = 0;
    while (ok == 0){

    printf("Adja meg a rendelés módosítani kívánt részének megfelelő betűt: \n");
    printf("C : Lakóingatlan CÍMÉNEK módosítása\n");
    printf("M : Lakóingatlan méretének módosítása\n");
    printf("R : Valamely részmunka módosítása\n");


    gets(str);
    switch (str[0])
    {
        case 'C':
            ok = 1;
            cimVagyMeretModosit(id, 1);
            break;
        case 'M':
            ok = 1;
            cimVagyMeretModosit(id, 0);
            break;
        case 'R':
            ok = 1;
            reszmunkamodosit(id);
            break;
        default:
            printf("Érvénytelen művelet\n");
            break;
    }
    }

}

void cimVagyMeretModosit(int id, int cim){
    int ok = 0;
    if (cim == 1)
        printf("Adja meg az új címet!");
    else
        printf("Adja meg az új méretet!");
    
    gets(str);


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
            ok = 1;
            fprintf(fp2, "%s", line);
            int j;
            read = getline(&line, &len, fp1);
            if (cim == 1){   
                fprintf(fp2, "%s\n", str);
                for(j = 0; j < 6; j++){
                    read = getline(&line, &len, fp1);
                    fprintf(fp2, "%s", line);
                }
            }
            else{
                fprintf(fp2, "%s", line);
                read = getline(&line, &len, fp1);
                fprintf(fp2, "%s\n", str);
                for(j = 0; j < 5; j++){
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
    if (ok == 1){
        printf("A módosítás sikeresen végrehajtva.\n");
            
    }
    else{
        printf("Sikertelen módosítás, nincs ilyen megrendelés!\n");
    }
}

void reszmunkamodosit(int id){
    int ok = 0;
    int valasztasok = 0;
    
    long rmid;
    int modositas;
    while (valasztasok == 0){
    printf("Adja meg a módosítani kívánt részmunka azonosítóját!\n");
    gets(str);
    rmid = atoi(str);
    printf("Adjon meg egy számot a módosítani kívánt adat szerint!\n");
    printf("0 : Részmunka megnevezése\n");
    printf("1 : Határidejének éve\n");
    printf("2 : Határidejének hónapja\n");
    printf("3 : Határidejének napja\n");
    printf("4 : Részmunka törlése\n");
    gets(str);
    modositas = atoi(str);
    valasztasok = 1;
    if (modositas < 4 && modositas >= 0){
        printf("Adja meg az új adatot!\n");
        gets(str);
    }
    else if (modositas != 4){
        printf("Érvénytelen adat!\n");
        valasztasok = 0;
    }
    }
    

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

    while ((read = getline(&line, &len, fp1)) != -1) {
        
        if (i % 8 == 0 && atoi(line) == id){
            getline(&line2, &len, fp1);
            getline(&line3, &len, fp1);
            getline(&lineRmAz, &len, fp1);
            
            if (modositas == 4 && atoi(lineRmAz) == rmid){
                for(j= 0; j < 4; j++)
                {
                    ok = 1;
                    getline(&line, &len, fp1);
                }
                
            }
            else if (atoi(lineRmAz) == rmid){
                fprintf(fp2, "%s", line);
                fprintf(fp2, "%s", line2);
                fprintf(fp2, "%s", line3);
                fprintf(fp2, "%s", lineRmAz);

                for (j = 0; j < modositas; j++){
                    getline(&line, &len, fp1);
                    fprintf(fp2, "%s", line);
                }
                getline(&line, &len, fp1);
                fprintf(fp2, "%s\n", str);
                j = 0;
                for (; j < 3-modositas; j++){
                    getline(&line, &len, fp1);
                    fprintf(fp2, "%s", line);
                }
                ok = 1;
            }
            else{
                fprintf(fp2, "%s", line);
                fprintf(fp2, "%s", line2);
                fprintf(fp2, "%s", line3);
                fprintf(fp2, "%s", lineRmAz);
                for(j= 0; j < 4; j++)
                {
                    getline(&line, &len, fp1);
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
        printf("A kért módosítás végrehajtva.\n");
    }
    else{
        printf("Nincs ilyen részmunka.\n");
    }

}