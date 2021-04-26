#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <errno.h> 
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
    printf("\nÚJ RENDELÉS FELVÉTELE\n\n");

    char cim[100];
    int meret;
    char merets[20];
    int rendben = 0;
    while (rendben == 0){
        printf("\nAdja meg a lakcímet!\n");
        gets(cim);
        if (cim == ""){
            printf("Érvénytelen lakcím!");
        }
        else{
            rendben = 1;
        }
    }
    rendben = 0;
    while (rendben == 0){
        printf("\nAdja meg a lakás méretét négyzetméterben, egész számra kerekítve!\n");
        gets(merets);
        meret = atoi(merets);
        if (meret < 1){
            printf("Érvénytelen méret!");
        }
        else{
            rendben = 1;
        }
    }
    long id = (unsigned long)time(NULL);

    printf("A megrendelés azonosítója: %i\n\n", id);
    printf("\nAdja meg a kért munkákat és határidejüket a következő formátumban:\n");
    printf("Elvégzendő feladat év hónap nap\n");
    printf("Például: Víz-gáz szerelés 2019 05 23\n");
    printf("A részmunka elfogadásához üssön entert! Ha nem kíván több részmunkát megadni, ismét üssön entert!\n");

    char str[80];
    const char s[2] = " ";
    char *token;
    char ** args[20];
    int ev;
    int honap;
    int nap;
    char * feladatnev[50];
    char buffer[10000];
    char snum[5];

    FILE * fp;
    fp = fopen("data.txt", "a");
    
    
    long rmid;
    
    while (1){
        gets(str);
        rmid = (unsigned long)time(NULL);
        token = strtok(str, s);
        args[0] = NULL;
        if (token != NULL){
            args[0] = token;
        }
   
        token = strtok(NULL, s);
        int i = 1;
        while( token != NULL ) {
            args[i] = token;
            token = strtok(NULL, s);
            i++;
        }
        if (i < 4){
            printf("Érvénytelen formátum!");
            break;
        }
            
        else{
            nap = atoi(args[i-1]);
            honap = atoi(args[i-2]);
            ev = atoi(args[i-3]);
            i = i - 3;
            int j = 0;
            while (j < i){
                strcat(feladatnev, args[j]);
                strcat(feladatnev, " ");
                j++;
            }
        }
        if (feladatnev == "" || ev < 2019 || honap < 0 || honap > 12 || nap < 1 || nap > 31){
            printf("Érvénytelen formátum!");
        }
        
        fprintf(fp, "%i\n%s\n%i\n%i\n%s\n%i\n%i\n%i\n", id, cim, meret, rmid, feladatnev, ev, honap, nap);
        //printf("%s, %s, %s\n", feladatnev, args[0], args[1]);
        int j = 0;
        for (j = 0; j < i; j++){
            memset(args[j], '\0', sizeof(args[j]));
        }
        memset(&args[0], 0, sizeof(args));
        //printf("%s\n%a\n%s\n", args[0], args[1], args[2]);
        memset(&feladatnev[0], 0, sizeof(feladatnev));
    }
    fclose (fp);
    printf("A megrendelés sikeresen elmentve %s azonosítóval.\n", id);
}