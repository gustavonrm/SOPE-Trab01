#ifndef _SIG_HANDLER_H
#define _SIG_HANDLER_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 

#include "log_file.h"

void start_handlers ();

void setV_flag ();

void sigint_handler ();

void sigusr1_handler (); 

void sigusr2_handler ();

#endif