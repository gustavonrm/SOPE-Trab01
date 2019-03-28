#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "defStruct.h"
#include "common.h"
#include "finder.h"

#define ERROR_OPEN -1;

int dir_read (defStruct *def);

#endif