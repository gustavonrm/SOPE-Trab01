#ifndef _FINDER_H
#define _FINDER_H

#define ERROR_FILES   1
#define ERROR_STAT    6
#define ERROR_CRYPTO  7

#include "defStruct.h"
#include "log_file.h"

int file_finder (defStruct *def, char *str);

#endif