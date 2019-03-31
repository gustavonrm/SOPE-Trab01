#include "common.h"

#define BUF_SIZE 256

FILE *fp = NULL;

void _wrt_to_file (char *file, char *str, int size);

void openFile (char *filename) {
  fp = fopen (filename, "wa");
  if (!fp)
    my_exit (ERROR_FILES, "Error opening file");
}

void closeFile() {
  fclose(fp);
}

int my_execlp (char *cmd, char *filename, char *ret) {
  if (cmd == NULL || filename == NULL)
    my_exit (ERROR_FILES, "Error opening files");
  
  int link[2];
  pid_t pid;
  char buf[BUF_SIZE +1];

  char delim[2] = " ";
  int aux = 0;

  if (pipe (link) == -1) 
    my_exit (ERROR_PIPE, "Error creating pipe");
  
  if (strcmp ("file", cmd) == 0){
    aux = 1;
    strcpy (delim, "\n");
  }

  pid = fork ();
  if (pid == -1)
    my_exit (ERROR_FORK, "Error creating fork");

  if (pid == 0) {   // Child
    dup2 (link[1], STDOUT_FILENO);
    close (link[0]);

    if (aux) {
      execlp (cmd, cmd, "-b", filename, NULL);  // Now writes to link[1]
    } else {
      execlp (cmd, cmd, filename, NULL);        // Now writes to link[1]
    }
  } else {          // Parent
    close (link[1]);

    read (link[0], buf, BUF_SIZE);

    waitpid (pid, NULL, 0);
  }
  
  buf[strcspn (buf, delim)] = '\0';            //Deletes \n at the end
  strcpy (ret, buf);
  
  return 0;
}

void wrt_to_str (char *str, char *txt) {
 strcat (str, txt);
 strcat (str, ",");
}

void file_write(int o_flag, char *filename, char *str){
  if (o_flag) {
    _wrt_to_file (filename, str, strlen (str));
  } else {
    printf ("%s\n", str);
  }
}

void my_exit (int err, char *str) {
  fprintf (stderr, "%s\n", str);
  exit (err);
}

int is_directory (char *filename) {
  struct stat st;

  stat (filename, &st);

  return S_ISDIR (st.st_mode);
}

void _wrt_to_file (char *file, char *str, int size) {
  fwrite (str, sizeof(char), size, fp);
  fwrite ("\n", sizeof(char), 1, fp);
}

