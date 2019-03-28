#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "defStruct.h"
#include "parser_in.h"
#include "common.h"
#include "finder.h"

void printUsage ();

int main (int argc, char *agrv[]){
  if (argc == 1) {
    printUsage (stdout);

    return 0;
  }

  defStruct *def = new_defStruct();
  if (!def) {
    fprintf (stderr, "Error allocating memory\n");
    return -1;
  }

  int ret = 0;
  
  ret = parse_input (argc, agrv, def);
  if (ret)
    printUsage (stderr);

  if (def -> v_flag){
    char *file_log;
    file_log = getenv ("LOGFILENAME");

    if (file_log != NULL) {
      defStruct_log (def, file_log);
    } else {
      fprintf (stderr, "Environment variable not set, LOGFILENAME\n");
      
      delete_defStruct(def);
      
      return -1;
    }
  }

  _print_struct (def);
  
  char str[512];
  file_finder (def, str);

  if (def -> o_flag) {
    wrt_to_file (def -> file_out, str, strlen(str));
  } else {
    printf ("%s\n", str);
  }

  delete_defStruct (def);
  
  return 0;
}

void printUsage (FILE *stream){
  fprintf (stream, "\nusage: forensic [-r] [-h [modes]] [-o filename] [-v] file|dir\n\n");
  fprintf (stream, "-r:\tanalizes all files in the directory or subdirectories\n");
  fprintf (stream, "-h:\tshows the crytographic hash. Supported modes: md5, sha1, sha256\n");
  fprintf (stream, "-o:\tsaves the data in filename\n");
  fprintf (stream, "-v:\tcreates a file and logs the execution in it. Name of file given in LOGFILENAME enviroment variable\n");
}