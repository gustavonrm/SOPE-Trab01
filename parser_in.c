#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defStruct.h"
#include "parser_in.h"

int parse_input (int argc, char *argv[], defStruct* def) {
  for (int i = 1; i < argc -1; i++) {
    if (strncmp (argv[i], "-", 1) == 0) {                   // Finding -
      switch (argv[i][1]) {
      case 'r':
        def -> r_flag = true;
        break;
      
      case 'h':
        def -> h_flag = true;
        defStruct_hash (def, argv[i+1]);                 // After -h must come the hash algorithms                                                       
        break;                                           // Which are in the next string
      
      case 'o':
        def -> o_flag = true;
        defStruct_out (def, argv[i+1]);
        break;
      
      case 'v':
        def -> v_flag = true;
        break;
      
      default:
        return -1; //change
      }
    }  
  }

  defStruct_target (def, argv[argc-1]);
  
  return 0;
}