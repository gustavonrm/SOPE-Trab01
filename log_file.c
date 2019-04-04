#include "log_file.h"

FILE *log_file = NULL;
struct timespec start;

double _getTime();

int initLog () {
  char *filename = getenv ("LOGFILENAME");
  if (!filename)
    return ERROR_FILES;
  
  log_file = fopen (filename, "wa");
  if (!log_file)
    return ERROR_FILES;
  
  if (clock_gettime (CLOCK_REALTIME, &start))
    return ERROR_GETTIME;

  return 0;
}

void closeLog () {
  fclose (log_file);
}

void wrt_log (char *str) {
  if (!str)
    return;

  fprintf (log_file, "%.2f - %.8d - %s\n", _getTime(), getpid(), str);
  fflush (log_file);
}

struct timespec _timeDiff (struct timespec end) {
  struct timespec ret;

  if ((end.tv_nsec - start.tv_nsec) < 0) {
    ret.tv_sec = end.tv_sec - start.tv_sec -1;
    ret.tv_nsec = end.tv_nsec - start.tv_nsec + 1000000000;
  } else {
    ret.tv_sec = end.tv_sec - start.tv_sec;
    ret.tv_nsec = end.tv_nsec - start.tv_nsec;
  }

  return ret;
}

double _getTime() {
  struct timespec curr;
  if (clock_gettime (CLOCK_REALTIME, &curr))
    return ERROR_GETTIME;
  
  struct timespec diff = _timeDiff (curr);

  return (double) diff.tv_sec * 1000 + (double) diff.tv_nsec / 1000;
}