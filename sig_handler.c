#include "sig_handler.h"

void sigint_handler(int signo)
{
    //TODO: ver melhor o q é suposto ser feito aqui, mas esta a receber o sinal
    printf("\nSuccefully ended all processes!\n");
    if (execlp("pkill", "pkill", "forensic", NULL) != -1)
        perror("pkill");
}

//define global file coount values
int n=0; //directories 
int m=0; //files

void sigusr1_handler(int signo){
    n++;
    printf("New directory: %d/%d directories/files at this time.\n",n,m); 
}

void sigusr2_handler(int signo){
    m++;
    printf("New directory: %d/%d directories/files at this time.\n",n,m); 
}