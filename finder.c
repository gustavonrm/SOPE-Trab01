#include <stdio.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "defStruct.h"
#include "common.h"

void _error_handler_finder (int err);

int _get_type (char *file, char *type);
int _get_stat (char *file, char *size, char *mode, char *aTime, char *mTime);
void _get_mode (mode_t mode, char *str);
int _get_hashSum (char *file, int alg, char *str);
void _format_time (time_t time, char *str, int size_str);

int file_finder (defStruct *def, char *str) {
  wrt_to_str (str, def -> target);

  char type[256];
  int ret;

  ret = _get_type (def -> target, type);
  if (ret != 0) {
    _error_handler_finder (ret);
    return -1;
  }

  wrt_to_str (str, type);

  char size[5], mode[4], aTime[20], mTime[20];

  ret = _get_stat (def->target, size, mode, aTime, mTime);
  if (ret !=0) {
    _error_handler_finder (ret);
    return -1;
  }
    
  wrt_to_str (str, size);
  wrt_to_str (str, mode);
  wrt_to_str (str, aTime);
  wrt_to_str (str, mTime);

  for (int i = 0; i < 3; i++) {
    if (def -> hash_alg[i]){
      char alg[256];
      ret = _get_hashSum (def ->target, i, alg);
      if(ret != 0) {
        _error_handler_finder (ret);
        return -1;
      }
      wrt_to_str (str, alg);
    }
  }
  return 0;
}

void _error_handler_finder (int err) {
  switch (err) {
  case 0:
    return;
    break;
  
  case -1:
    fprintf (stderr, "Error files cant be null\n");
    return;
    break;

  case -2:
    fprintf (stderr, "Error creating a pipe\n");
    return;
    break;
  
  case -3:
    fprintf (stderr, "Error creating a new process\n");
    return;
    break;

  case -4:
    fprintf (stderr, "Error getting the stat struct\n");
    return;
    break;
  
  case -5:
    fprintf (stderr, "Error calculating cryptographic sums \n");
    return;
    break;
  }
}

int _get_type (char *file, char *type) {
  int ret;
  
  ret = my_execlp ("file", file, type);

  return ret;
}

int _get_stat (char *file, char *size, char *mode, char *aTime, char *mTime) {
  struct stat buf;
  int ret;

  ret = stat (file, &buf);
  if(ret != 0)
    return -4;

  sprintf (size, "%ld", buf.st_size);
  _get_mode (buf.st_mode, mode);
  _format_time (buf.st_atime, aTime, 20);
  _format_time (buf.st_mtime, mTime, 20);

  return 0;
}

int _get_hashSum (char *file, int alg, char *str) {
  int ret;

  switch (alg) {
  case 0:
    
    ret = my_execlp ("md5sum", file, str);
    return ret;
    break;
  
  case 1:
    ret = my_execlp ("sha1sum", file, str);
    return ret;
    break;
  
  case 2:
    ret = my_execlp ("sha256sum", file, str);
    return ret;
    break;
  
  default:
    return -5;
    break;
  }
}

void _get_mode (mode_t mode, char *str) {
  if (mode & S_IRUSR)
    strcat (str, "r");
  
  if (mode & S_IWUSR)
    strcat (str, "w");
  
  if (mode & S_IXUSR)
    strcat (str, "x");
}

void _format_time (time_t time, char *str, int size_str) {
  struct tm *timeinfo;

  timeinfo = localtime (&time);
  strftime (str, size_str, "%FT%T", timeinfo);
}