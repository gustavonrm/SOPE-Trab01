#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h> 

#include <sys/types.h>
#include <sys/stat.h>

#include "defStruct.h"
#include "common.h"
#include "finder.h"
#include "log_file.h"

#define ERROR_OPEN 10
#define ERROR_LSTAT 11
#define ERROR_FILE_DIR 12

int dir_read (defStruct *def);

#endif