#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defStruct.h"
#include "parser_in.h"
#include "common.h"

int parse_input (int argc, char *argv[], defStruct* def);

int _error_handler_parser (int err);

int parse_input (int argc, char *argv[], defStruct* def) {
  int ret = 0;

  for (int i = 1; i < argc -1; i++) {
    if (strncmp (argv[i], "-", 1) == 0) {                   // Finding -
      switch (argv[i][1]) {
      case 'r':
        def -> r_flag = true;
        break;
      
      case 'h':
        def -> h_flag = true;
        ret = defStruct_hash (def, argv[i+1]);            // After -h must come the hash algorithms                                                       
                                                          // Which are in the next string  
        if(ret)
          my_exit(ret, "Error input cryptographic algorithms");

        break;
      
      case 'o':
        def -> o_flag = true;
        ret = defStruct_out (def, argv[i+1]);

        if (ret)
          my_exit (ret, "Error allocating memory, output");

        break;
      
      case 'v':
        def -> v_flag = true;
        break;
      
      default:
        return -1;
      }
    }  
  }

  ret = defStruct_target (def, argv[argc-1]);
  
  if (ret)
    my_exit (ret, "Error allocating memory, target");

  if (!def -> r_flag && is_directory(def -> target))
    my_exit (ERROR_NFILE, "Input is not a valid file");

  return 0;
}