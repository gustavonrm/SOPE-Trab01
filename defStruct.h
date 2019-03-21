#ifndef _DEFSTRUCT_H
#define _DEFSTRUCT_H

typedef enum {false, true} bool; 

typedef struct {
  int r_flag;
  
  int h_flag;
  int* hash_alg;
  
  int o_flag;
  char *file_out;
  
  int v_flag; 
  char *file_log;

  char *target;
} defStruct;


// Allocates memory for the struct
defStruct* new_defStruct();

// Allocates memory for the hash_alg array
// Changes its values according to the usr chosen alg
// [0] true = md5
// [1] true = sha1
// [2] true = sha256
int defStruct_hash(defStruct *def, char *algs);

int defStruct_out (defStruct *def, char *file);

int defStruct_log (defStruct *def, char *file);

int defStruct_target (defStruct *def, char *target);

void delete_defStruct(defStruct *def);

void _print_struct(defStruct *def);
#endif