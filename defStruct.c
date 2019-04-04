#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defStruct.h"

defStruct* new_defStruct () {
  defStruct* def;

  def = (defStruct*)malloc (sizeof (defStruct));
  if (!def)
    return ERROR_NULL;
  
  def -> r_flag = false;
  
  def -> h_flag = false;
  def -> hash_alg = NULL;
  
  def -> o_flag = false;
  def -> file_out = NULL;
  
  def -> v_flag = false;
  def -> file_log = NULL;
  
  def -> file_log = NULL;
  
  def -> higher_pid = false;

  def -> target = NULL;

  return def;
}

int defStruct_hash (defStruct *def, char *algs) {
  if (def == NULL || algs == NULL)
    return ERROR_FILES;

  def -> hash_alg = (int *)calloc (3, sizeof (def -> hash_alg));
  if (def -> hash_alg == NULL)
    return ERROR_ALLOC;

  char *tok;
  tok = strtok (algs, ",");
  int alg = true;

  while (tok != NULL){
    if (strcmp (tok, "md5") == 0) {
      alg = false;
      def -> hash_alg[0] = true;
    } else if (strcmp (tok, "sha1") == 0) {
      alg = false;
      def -> hash_alg[1] = true;
    } else if (strcmp (tok, "sha256") == 0) {
      alg = false;
      def -> hash_alg[2] = true;
    } else {
      return ERROR_ALG;
    }

    tok = strtok (NULL, ",");
  }
  
  if (alg)
    return ERROR_ALG;
  
  return SUCCESS;
}

int defStruct_out (defStruct *def, char *file) {
  if (def == NULL || file == NULL)
    return ERROR_FILES;

  def -> file_out = (char *)malloc (sizeof (char) * strlen (file));
  if (!def -> file_out)
    return ERROR_ALLOC;

  strcpy (def -> file_out, file);

  return SUCCESS;
}

int defStruct_log (defStruct *def, char *file) {
  if (def == NULL || file == NULL)
    return ERROR_FILES;

  def -> file_log = (char *)malloc (sizeof (char) * strlen (file));
  if (!def -> file_log)
    return ERROR_ALLOC;

  strcpy (def -> file_log, file);

  return SUCCESS;
}

int defStruct_target (defStruct *def, char *target) {
  if (def == NULL || target == NULL) 
    return ERROR_FILES;
  
  def -> target = (char *)malloc (sizeof (char) * strlen (target));
  if (!def -> target)
    return ERROR_ALLOC;
  
  strcpy (def -> target, target);

  return SUCCESS;
}

void delete_defStruct (defStruct *def){
  if (!def)
    return;

  free (def -> hash_alg);
  free (def -> file_out);
  free (def -> file_log);
  free (def -> target);

  free (def);
}

void _print_struct (defStruct *def) {
  printf ("R_FLAG: %d\n", def -> r_flag);
  
  printf ("H_FLAG: %d\n", def -> h_flag);
  if (def -> hash_alg != NULL){
    for (int i = 0; i < 3; i++) {
      printf ("hash_alg[%d]: %d\n", i, def -> hash_alg[i]);
    }
  }
  
  printf ("O_FLAG: %d\n", def -> o_flag);
  if (def -> file_out != NULL)
    printf ("file out: %s\n", def -> file_out);

  printf ("V_FLAG: %d\n", def -> v_flag);
  if (def -> file_log != NULL)
    printf ("log file: %s\n", def -> file_log);

  if (def -> target != NULL)
    printf ("target: %s\n", def -> target);
}