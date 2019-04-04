#include "directory.h"

int _ignore_dot (char *filename);
void _rearange_def (defStruct *old, defStruct *new, char *filename);

int dir_read (defStruct *def) {
  DIR *dir;
  struct dirent *dentry;
  struct stat stat_entry;

  int v_flag = def -> v_flag;
  int size = strlen (def -> target);
  char main_folder[size];
  strcpy (main_folder, def -> target);
  
  //subfolders
  pid_t pid;

  char str[512];
  str[0] = '\0';

  // Open dir
  dir = opendir (def -> target);
  if (!dir)
    my_exit (ERROR_OPEN, "Error opening directory");

  // Output files
  while ((dentry = readdir (dir)) != NULL) {
    //to test signal - sleep should be removed
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
        
        _rearange_def (def, sample, pathname);
      
        strcpy (str, "");
        file_finder (sample, str);

        file_write (sample->o_flag, str, def->higher_pid);

        delete_defStruct (sample);

      }
      if (S_ISDIR (stat_entry.st_mode)) {
        defStruct *sample = new_defStruct ();
        if (!sample)
          my_exit(-1, "error creating new struct");
        
        _rearange_def (def, sample, pathname);

        if (def->o_flag)
          kill (def->higher_pid, SIGUSR1);

        pid = fork ();
        if (pid == 0) {
          //ignore all SIGINTS
          struct sigaction action,orig_action; 
          action.sa_handler = SIG_IGN;
          sigemptyset(&action.sa_mask);
          action.sa_flags=0; 

          sigaction(SIGINT,&action,&orig_action); 

          if (v_flag) {
            char log[51];
            snprintf (log, 51, "Created process with pid %.8d (child-dir_read)", getpid());
            sleep(1);
            wrt_log (log);
          }
          dir_read (sample);

           sigaction(SIGINT,&orig_action,NULL); 
          exit(0);
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

void _rearange_def (defStruct *old, defStruct *new, char *filename) {
  new -> h_flag = old -> h_flag;
  new -> hash_alg = old -> hash_alg;

  new -> o_flag = old -> o_flag;
  defStruct_out (new, old -> file_out);

  new -> v_flag = old -> v_flag;
  
  defStruct_target (new, filename);
}