#include "directory.h"

int _ignore_dot (char *filename);
void _rearange_def (defStruct *old, defStruct *new,char *file_name); 

int dir_read (defStruct *def) {
    //bugs
    DIR *dir;
    struct dirent *dentry;
    struct stat stat_entry;
    
    int size = strlen (def->target);
    char main_folder[size];
    strcpy (main_folder, def->target);
    
    char str[512];

    // Open dir
    dir = opendir (def -> target);
    if (!dir)
      my_exit (ERROR_OPEN, "Error opening directory");
    
    // Output files
    while ((dentry = readdir (dir)) != NULL) {
      if (_ignore_dot (dentry -> d_name)) {
        char pathname[512] = {};
        sprintf (pathname, "%s/%s", main_folder, dentry->d_name);
        
        if (lstat (pathname, &stat_entry))
          my_exit (ERROR_LSTAT, "Error getting stat struct from folder"); // Assim ou com perror? a que se escolher tem que ser igual em todos
        
        if (S_ISDIR (stat_entry.st_mode)) {
          //TODO fork()
          
        } else if (S_ISREG(stat_entry.st_mode)) {
          //READ
          defStruct *sample = new_defStruct ();
          if (!sample)
            my_exit (-1, "error creating new struct");
          _rearange_def (def, sample, pathname);
          
          strcpy (str, "");
          file_finder (sample, str);
          
          file_write (sample -> o_flag, sample -> file_log, str);
        }
      }
    }
    
    closedir (dir);

    return 0;
}

int _ignore_dot (char *filename) {
  if (strcmp (filename, ".") == 0)
      return 0;
  else if (strcmp (filename, "..") == 0)
      return 0;
  else
      return 1;
}

void _rearange_def (defStruct *old, defStruct *new, char *file_name) {
  new -> h_flag = old -> h_flag;
  new -> hash_alg = old -> hash_alg;
  
  new -> o_flag = old -> o_flag;
  defStruct_out (new, old -> file_out);
  
  new -> v_flag = old -> v_flag;
  defStruct_log (new, old -> file_log);

  defStruct_target (new, file_name);
}