#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/stat.h>

#include "defStruct.h"

#define ERROR_FILES 1
#define ERROR_PIPE  2
#define ERROR_FORK  3

int my_execlp (char *cmd, char *filename, char *ret);

void wrt_to_str (char *str, char *txt);

void wrt_to_file (char *file, char *txt, int size);

void file_write (defStruct *def,char *str);

void my_exit (int err, char *str);

int is_directory (char *filename);

//https://stackoverflow.com/questions/4761764/how-to-remove-first-three-characters-from-string-with-c
void chopN (char *str, size_t n);

#endif