#ifndef _DEFSTRUCT_H
#define _DEFSTRUCT_H

#include <sys/types.h>

#define SUCCESS     0
#define ERROR_NULL  NULL
#define ERROR_ALLOC 5
#define ERROR_FILES 1
#define ERROR_ALG   4

typedef enum {false, true} bool; 

typedef struct {
  int r_flag;
  
  int h_flag;
  int* hash_alg;
  
  int o_flag;
  char *file_out;
  
  int v_flag; 

  pid_t higher_pid; 

  char *target;

} defStruct;


// Allocates memory for the struct
defStruct* new_defStruct ();

// Allocates memory for the hash_alg array
// Changes its values according to the usr chosen alg
// [0] true = md5
// [1] true = sha1
// [2] true = sha256
int defStruct_hash (defStruct *def, char *algs);

int defStruct_out (defStruct *def, char *file);

int defStruct_target (defStruct *def, char *target);

void delete_defStruct (defStruct *def);

//DEBUG
void _print_struct (defStruct *def);

#endif