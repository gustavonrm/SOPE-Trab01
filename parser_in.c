#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defStruct.h"
#include "parser_in.h"

int parse_input (int argc, char *argv[], defStruct* def);

int _error_handler (int err);

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
        if (_error_handler(ret))
          return -1;
        break;
      
      case 'o':
        def -> o_flag = true;
        ret = defStruct_out (def, argv[i+1]);

        if (_error_handler(ret))
          return -1;
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
  
  if (_error_handler(ret))
    return -1;

  return 0;
}

int _error_handler (int err) {
  switch (err) {
  case -1:
      fprintf (stderr, "1 Error allocating memory\n");
      return -1;
      break;
  
  case -2:
    fprintf (stderr, "Error missing files\n");
    return -1;
    break;
  
  case -3:
    fprintf (stderr, "Error on the cryptographic hash algorithms\n");
    return -1;
    break;

  case 0:
    return 0;
    break;
  
  default:
    return -1;
    break;
  }
}