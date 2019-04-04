#include "sig_handler.h"

int v_flag;

//define global file coount values
static int n=0; //directories 
static int m=0; //files

void start_handlers (int v) {
  v_flag = 0;

  //SIGINT INSTALL
  struct sigaction action_int;
  action_int.sa_handler = sigint_handler;
  sigemptyset (&action_int.sa_mask);
  action_int.sa_flags = 0;

  sigaction (SIGINT, &action_int, NULL);

  //SIGUSR1 INSTALL
  struct sigaction action_usr1;
  action_usr1.sa_handler = sigusr1_handler;
  sigemptyset (&action_usr1.sa_mask);
  action_usr1.sa_flags = 0;

  sigaction (SIGUSR1, &action_usr1, NULL);

  //SIGUSR2 INSTALL
  struct sigaction action_usr2;
  action_usr2.sa_handler = sigusr2_handler;
  sigemptyset (&action_usr1.sa_mask);
  action_usr2.sa_flags = 0;

  sigaction (SIGUSR2, &action_usr2, NULL);
}

void setV_flag (int v) {
  v_flag = v;
}

void sigint_handler (int signo) {
  if (v_flag){
    char *log = NULL;
    asprintf (&log, "SIGNAL INT received");
    sleep(1);
    wrt_log (log);
    free(log);
  }

  //TODO: ver melhor o q é suposto ser feito aqui, mas esta a receber o sinal
  printf ("\nSuccefully ended all processess!\n");
  if (execlp("pkill", "pkill", "forensic", NULL) != -1)
    perror("pkill");
}

void sigusr1_handler (int signo){
  if (v_flag){
    char *log = NULL;
    asprintf (&log, "SIGNAL USR1 received");
    sleep(1);
    wrt_log (log);
    free (log);
  }

  n++;
  printf ("New directory: %d/%d directories/files at this time.\n",n,m); 
}

void sigusr2_handler (int signo){
  if (v_flag) {
    char *log = NULL;
    asprintf (&log, "SIGNAL USR2 received");
    sleep(1);
    wrt_log (log);
    free (log);
  }
  m++;
  printf ("New directory: %d/%d directories/files at this time.\n",n,m); 
}