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
#include "sig_handler.h"

void printUsage ();

int main (int argc, char *agrv[]) {
  // Argument check
  if (argc == 1) {
    printUsage (stdout);
    return 0;
  }

  //SIGINT INSTALL
  struct sigaction action_int;
  action_int.sa_handler = sigint_handler;
  sigemptyset (&action_int.sa_mask);
  action_int.sa_flags = 0;

  sigaction (SIGINT, &action_int, NULL);

  //SIGUSR1 INSTALL
  struct sigaction action_usr1;
  action_usr1.sa_handler = sigusr1_handler;
  sigemptyset (&action_usr1.sa_mask);
  action_usr1.sa_flags = 0;

  sigaction (SIGUSR1, &action_usr1, NULL);

  //SIGUSR2 INSTALL
  struct sigaction action_usr2;
  action_usr2.sa_handler = sigusr2_handler;
  sigemptyset (&action_usr1.sa_mask);
  action_usr2.sa_flags = 0;

  sigaction (SIGUSR2, &action_usr2, NULL);

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

  ret = parse_input (argc, agrv, def);
  if (ret)
    printUsage (stderr);

  // Log file processing
  if (def->v_flag) {
    char *file_log;
    file_log = getenv ("LOGFILENAME");

    if (file_log != NULL) {
      defStruct_log(def, file_log);
    } else {
      fprintf (stderr, "Environment variable not set, LOGFILENAME\n");

      delete_defStruct (def);

      return -1;
    }
  }

  if (def->o_flag)
    openFile (def->file_out);

  // Directory
  if (def->r_flag) {
    if(def->o_flag)
          kill (def->higher_pid,SIGUSR1);
    dir_read (def);
  } else { // Single file
    char str[512];
    file_finder (def, str);
    file_write (def->o_flag, str,def->higher_pid);
  }

  // Exiting
  if (def->o_flag)
    closeFile();

  delete_defStruct (def);

  return 0;
}

void printUsage (FILE *stream) {
  fprintf (stream, "\nusage: forensic [-r] [-h [modes]] [-o filename] [-v] file|dir\n\n");
  fprintf (stream, "-r:\tanalizes all files in the directory or subdirectories\n");
  fprintf (stream, "-h:\tshows the crytographic hash. Supported modes: md5, sha1, sha256\n");
  fprintf (stream, "-o:\tsaves the data in filename\n");
  fprintf (stream, "-v:\tcreates a file and logs the execution in it. Name of file given in LOGFILENAME enviroment variable\n");
}