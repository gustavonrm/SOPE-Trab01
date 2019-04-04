#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "defStruct.h"
#include "parser_in.h"
#include "common.h"
#include "finder.h"
#include "directory.h"
#include "log_file.h"
#include "sig_handler.h"

void printUsage ();

int main (int argc, char *argv[]) {
  // Argument check
  if (argc == 1) {
    printUsage (stdout);
    return 0;
  }

  start_handlers ();

  // Building struct
  defStruct *def = new_defStruct ();
  if (!def) {
    fprintf(stderr, "Error allocating memory\n");
    return -1;
  }

  //to use on signals
  def->higher_pid = getpid ();
  printf ("pid: %d\n",def->higher_pid);

  int ret = 0;

  ret = parse_input (argc, argv, def);
  if (ret)
    printUsage (stderr);

  setV_flag (def ->v_flag);

  // Log file processing
  if (def->v_flag) {
    initLog ();
    
    char str[7 + argc * 7];
    str[0] = '\0';
    strcat (str, "COMMAND");
    for (int i = 0; i < argc; i++) {
      strcat (str, " ");
      strcat (str, argv[i]);
    }
    sleep(1);
    wrt_log (str);
  }

  openFile (def->file_out);

  // Directory
  if (def->r_flag) {
    if(def->o_flag)
          kill (def->higher_pid,SIGUSR1);
    dir_read (def);
  } else { // Single file
    char str[512];
    str[0] = '\0';
    file_finder (def, str);
    file_write (def->o_flag, str,def->higher_pid);
  }

  // Exiting
  if (def->o_flag){
    closeFile();
    printf("Data saved on file %s\nExecution saved on file...\n",def->file_out);
  }
  
  if (def -> v_flag) {
    closeLog();
  }

  delete_defStruct (def);
  puts("Finish");
  return 0;
}

void printUsage (FILE *stream) {
  fprintf (stream, "\nusage: forensic [-r] [-h [modes]] [-o filename] [-v] file|dir\n\n");
  fprintf (stream, "-r:\tanalizes all files in the directory or subdirectories\n");
  fprintf (stream, "-h:\tshows the crytographic hash. Supported modes: md5, sha1, sha256\n");
  fprintf (stream, "-o:\tsaves the data in filename\n");
  fprintf (stream, "-v:\tcreates a file and logs the execution in it. Name of file given in LOGFILENAME enviroment variable\n");
}