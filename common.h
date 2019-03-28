#ifndef _COMMON_H
#define _COMMON_H

#define ERROR_FILES 1
#define ERROR_PIPE  2
#define ERROR_FORK  3

int my_execlp (char *cmd, char *filename, char *ret);

void wrt_to_str (char *str, char *txt);

void wrt_to_file (char *file, char *txt, int size);

void my_exit (int err, char *str);

int is_directory (char *filename);

#endif