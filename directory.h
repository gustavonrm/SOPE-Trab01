#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h> 

#include <sys/types.h>
#include <sys/stat.h>

#include "defStruct.h"
#include "common.h"
#include "finder.h"

#define ERROR_OPEN 10;
#define ERROR_FILE_DIR 11; 

int dir_read (defStruct *def);
//ultils
int ignore_dot(char *filename); 

void rearange_def(defStruct *old, defStruct *new,char *file_name); 

int dir_write(char **str, defStruct *def);

#endif