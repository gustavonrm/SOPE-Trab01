#include "directory.h"

int _ignore_dot (char *filename);
void _rearange_def (defStruct *old, defStruct *new, char *path, char *filename);

int dir_read (defStruct *def) {
  DIR *dir;
  struct dirent *dentry;
  struct stat stat_entry;

  int size = strlen (def->path);
  char main_folder[size];
  strcpy (main_folder, def->path);
  
  //subfolders
  pid_t pid;
  int status;

  char str[512];

  // Open dir
  dir = opendir (def->path);
  if (!dir)
    my_exit (ERROR_OPEN, "Error opening directory");

  // Output files
  while ((dentry = readdir (dir)) != NULL) {
    //to test signal - sleep should be removes
    //sleep(1);
    if (_ignore_dot(dentry->d_name)) {
      char pathname[512] = {};
      sprintf (pathname, "%s/%s", main_folder, dentry->d_name);
      
      if (lstat (pathname, &stat_entry))
        my_exit (ERROR_LSTAT, "Error getting stat struct from folder"); // Assim ou com perror? a que se escolher tem que ser igual em todos

      if (S_ISREG (stat_entry.st_mode)) {
        //READ
        defStruct *sample = new_defStruct ();
        if (!sample)
          my_exit(-1, "error creating new struct");
        
        _rearange_def (def, sample, pathname, dentry -> d_name);
      
        strcpy (str, "");
        file_finder( sample, str);

        file_write (sample->o_flag, str, def->higher_pid);

        delete_defStruct (sample);

      } else if (S_ISDIR (stat_entry.st_mode)) {
        defStruct *sample = new_defStruct ();
        if (!sample)
          my_exit(-1, "error creating new struct");
        
        _rearange_def (def, sample, pathname, dentry -> d_name);

        if (def->o_flag)
          kill (def->higher_pid, SIGUSR1);

        pid = fork ();
        if (pid == 0) {
          dir_read (sample);
          return 0;
        } else {
          wait (&status);
        }

        delete_defStruct (sample);
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

void _rearange_def (defStruct *old, defStruct *new, char *path, char *filename) {
  new -> h_flag = old -> h_flag;
  new -> hash_alg = old -> hash_alg;

  new -> o_flag = old -> o_flag;
  defStruct_out (new, old -> file_out);

  new -> v_flag = old -> v_flag;
  defStruct_log(new, old -> file_log);
  
  defStruct_filename (new, filename);
 
  defStruct_path (new, path);
 
}