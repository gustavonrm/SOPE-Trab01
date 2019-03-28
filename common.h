#ifndef _COMMON_H
#define _COMMON_H

#include "defStruct.h"

int my_execlp (char *cmd, char *filename, char *ret);

void wrt_to_str (char *str, char *txt);

void wrt_to_file (char *file, char *txt, int size);

void file_read(defStruct *def,char *str);

#endif