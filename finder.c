#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "defStruct.h"
#include "common.h"
#include "finder.h"

int _get_type (char *file, char *type, int v_flag);
int _get_stat (char *file, char *size, char *mode, char *aTime, char *mTime);
void _get_mode (mode_t mode, char *str);
int _get_hashSum (char *file, int alg, char *str, int v_flag);
void _format_time (time_t time, char *str, int size_str);

int file_finder (defStruct *def, char *str) {
  wrt_to_str (str, def -> target);
  
  char type[256];
  int ret;

  ret = _get_type (def -> target, type, def ->v_flag);
  if (ret)
    my_exit (ret, "Error getting type");

  wrt_to_str (str, type);

  char size[5], mode[4], aTime[20], mTime[20];

  ret = _get_stat (def -> target, size, mode, aTime, mTime);
  if (ret)
    my_exit (ret, "Error creating stat struct");

  wrt_to_str (str, size);
  wrt_to_str (str, mode);
  wrt_to_str (str, aTime);
  wrt_to_str (str, mTime);

  if (def->h_flag) { 
    for (int i = 0; i < 3; i++) {
      if (def->hash_alg[i]) {
        char alg[256];
        ret = _get_hashSum (def -> target, i, alg, def -> v_flag);
        if (ret)
          my_exit (ret, "Error calculating cryptographic sums");

        wrt_to_str (str, alg);
      }
    }
  }

  if (def -> v_flag) {
    char *log = NULL;
    asprintf(&log, "ANALIZED %s with pid %.8d", def -> target, getpid());
    wrt_log (log);
    free (log);
  }
  
  return 0;
}

int _get_type (char *file, char *type, int v_flag) {
  int ret;
  
  //if patch from dir or file
  if (strchr (file, '/') == NULL)
    ret = my_execlp ("file", file, type, v_flag);
  else 
    ret = my_execlp ("file", file, type, v_flag);

  return ret;
}

int _get_stat (char *file, char *size, char *mode, char *aTime, char *mTime) {
  struct stat buf;
  int ret;
  
  //if patch from dir or file
  if (strchr (file, '/') == NULL) {
    ret = lstat (file, &buf);
    if (ret != 0)
      return -1;
  } else {
    ret = stat (file, &buf);
    if (ret != 0)
      return -1;
  }

  sprintf (size, "%ld", buf.st_size);
  _get_mode (buf.st_mode, mode);
  _format_time (buf.st_atime, aTime, 20);
  _format_time (buf.st_mtime, mTime, 20);
 
  return 0;
}

int _get_hashSum (char *file, int alg, char *str, int v_flag) {
  int ret;

  switch (alg) {
  case 0: 
    ret = my_execlp ("md5sum", file, str, v_flag);
    return ret;
    break;

  case 1:
    ret = my_execlp ("sha1sum", file, str, v_flag);
    return ret;
    break;

  case 2:
    ret = my_execlp ("sha256sum", file, str, v_flag);
    return ret;
    break;

  default:
    return -1;
    break;
  }
}

void _get_mode (mode_t mode, char *str) {
  if (mode & S_IRUSR)
    strcat(str, "r");

  if (mode & S_IWUSR)
    strcat(str, "w");

  if (mode & S_IXUSR)
    strcat(str, "x");
}

void _format_time (time_t time, char *str, int size_str) {
  struct tm *timeinfo;

  timeinfo = localtime (&time);
  strftime (str, size_str, "%FT%T", timeinfo);
}