#ifndef _SIG_HANDLER_H
#define _SIG_HANDLER_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 

#include "log_file.h"

void start_handlers ();

void setV_flag (int v);

void sigint_handler (int signo);

void sigusr1_handler (int signo); 

void sigusr2_handler (int signo);

#endif