#include "common.h"

#define BUF_SIZE 256

FILE *out_desc = NULL;

void openFile (char *filename) {
  out_desc = fopen (filename, "wa");
  if (!out_desc)
    out_desc = stdout;
}

void closeFile () {
  fclose (out_desc);
}

int my_execlp (char *cmd, char *filename, char *ret, int v_flag) {
  if (cmd == NULL || filename == NULL)
    my_exit (ERROR_FILES, "Error opening files");

  int link[2];
  pid_t pid;
  char buf[BUF_SIZE + 1];

  char delim[2] = " ";
  int aux = 0;

  if (pipe (link) == -1)
    my_exit (ERROR_PIPE, "Error creating pipe");

  if (strcmp ("file", cmd) == 0) {
    aux = 1;
    strcpy (delim, "\n");
  }

  pid = fork ();
  if (pid == -1)
    my_exit (ERROR_FORK, "Error creating fork");

  if (pid == 0) { // Child
    if (v_flag){
      char log[52];
      snprintf (log, 52, "Created process with pid %.8d (child-my_execlp)", getpid ());
      sleep(1);
      wrt_log (log);
    }

    dup2 (link[1], STDOUT_FILENO);
    close (link[0]);

    if (aux)
      execlp (cmd, cmd, "-b", filename, NULL); // Now writes to link[1]
    else
      execlp (cmd, cmd, filename, NULL); // Now writes to link[1]

  } else { // Parent
    if (v_flag){
      char log[53];
      snprintf (log, 53, "Created process with pid %.8d (parent-my_execlp)", pid);
      sleep(1);
      wrt_log (log);
    }
    
    close (link[1]);
    read (link[0], buf, BUF_SIZE);
    waitpid (pid, NULL, 0);
  }

  buf[strcspn (buf, delim)] = '\0'; //Deletes \n at the end
  strcpy (ret, buf);

  return 0;
}

void wrt_to_str (char *str, char *txt) {
  strcat (str, txt);
  strcat (str, ",");
}

void file_write (int o_flag, char *str, pid_t pid) {
  if (o_flag)
    kill (pid, SIGUSR2);
  
  fprintf (out_desc, "%s\n", str);
  fflush (out_desc);
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
void _wrt_to_file (char *str, int size) {
  fwrite (str, sizeof(char), size, out_desc);
  fwrite ("\n", sizeof(char), 1, out_desc);
  fflush (out_desc);
}
void chopN(char *str, size_t n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
        n = len;
    memmove(str, str+n, len - n + 1);
}

