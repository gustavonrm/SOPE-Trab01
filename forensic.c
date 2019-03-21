#include <stdio.h>
#include <stdlib.h>

#include "defStruct.h"
#include "parser_in.h"

void printUsage ();

int main (int argc, char *agrv[], char *envp[]){
  if (argc == 1){
    printUsage (stdout);

    return -1;
  }

  defStruct *def = new_defStruct();
  if (!def) {
    fprintf(stderr, "2 Error allocating memory\n");
    return -1;
  }

  int ret = 0;
  ret = parse_input (argc, agrv, def);
  if(ret)
    printUsage (stderr);

  _print_struct (def);

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