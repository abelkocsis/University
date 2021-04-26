#include <stdio.h>
#include <stdlib.h>
//call it with some parameters from the command line 

int main(int argc,char ** argv) 
//char** means an array of character arrays = array of strings
{
printf("Program: %s\n",argv[0]);

 int i;
 printf("Number of command line arguments are: %i\n",argc);
 for (i=1;i<argc;i++){
  printf("%i. argument is (%i)\n",i,atoi(argv[i])+1);
 }
 return 0;
}
