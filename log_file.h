#ifndef _LOG_FILE_H
#define _LOG_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ERROR_FILES 1
#define ERROR_GETTIME 13

int initLog ();

void closeLog ();

void wrt_log (char *str);

#endif