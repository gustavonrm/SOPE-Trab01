#include <stdio.h>
#include <stdlib.h>

#include "defStruct.h"
#include "parser_in.h"

void printUsage();

int main(int argc, char *agrv[], char *envp[]){
  if(argc == 1){
    printUsage();

    return -1;
  }

  defStruct *def = new_defStruct();
  if(!def)
    return -1;
  
  parse_input (argc, agrv, def);
  
  _print_struct(def);
  delete_defStruct(def);
  
  return 0;
}

void printUsage(){
  printf("usage: forensic [-r] [-h [modes]] [-o filename] [-v] file|dir\n\n");
  printf("-r:\tanalizes all files in the directory or subdirectories\n");
  printf("-h:\tshows the crytographic hash. Supported modes: md5, sha1, sha256\n");
  printf("-o:\tsaves the data in filename");
  printf("-v:\tcreates a file and logs the execution in it. Name of file given in LOGFILENAME enviroment variable\n");
}