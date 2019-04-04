#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/stat.h>

#include "log_file.h"

#define ERROR_FILES 1
#define ERROR_PIPE  2
#define ERROR_FORK  3

void openFile (char *filename);

void closeFile ();

int my_execlp (char *cmd, char *filename, char *ret, int v_flag);

void wrt_to_str (char *str, char *txt);

void file_write (int o_flag, char *str,pid_t pid);

void my_exit (int err, char *str);

int is_directory (char *filename);

#endif