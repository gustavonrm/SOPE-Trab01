#include "directory.h"

int dir_read (defStruct *def) {
    //bugs
    DIR *dir;
    struct dirent *dentry;
    struct stat stat_entry;
    //save main file name
    int size = strlen (def->target);
    char main_folder[size];
    strcpy (main_folder, def->target);
    char str[512];
    char *lines[16];
    int ln = 0;

    //open dir
    if ((dir = opendir (def->target)) == NULL) {
        perror (def->target);
        return ERROR_OPEN;
    }
    //output files
    while ((dentry = readdir (dir)) != NULL) {
        if (ignore_dot (dentry->d_name) == 0) {
            char pathname[512] = {};
            sprintf (pathname, "%s/%s", main_folder, dentry->d_name);
            //printf("%s\n", pathname);
            if (lstat(pathname, &stat_entry) == -1) {
                perror ("lstat ERROR");
                return 10;
            }
            if (S_ISDIR (stat_entry.st_mode)) {
                //TODO fork()
                //printf("dir: %s\n", dentry->d_name);
            } else if (S_ISREG(stat_entry.st_mode)) {
                //printf("file: %s\n", dentry->d_name);
                //READ
                defStruct *sample = new_defStruct ();
                rearange_def (def, sample, pathname);
                strcpy (str, "");
                file_finder (sample, str);
                chopN (str, size + 1);
                //file_write(sample,str);
                //printf("%s\n",str);
                lines[ln] = malloc (strlen (str) + 1);
                strcpy (lines[ln], str);
                ln++;
                //bug tests
                //printf("i:%d\n", i);
                //i++;
            }
        }
    }
    dir_write (lines, def);
    closedir (dir);

    return 0;
}

int ignore_dot (char *filename) {
    if (strcmp (filename, ".") == 0)
        return 1;
    else if (strcmp (filename, "..") == 0)
        return 1;
    else
        return 0;
}

void rearange_def (defStruct *old, defStruct *new, char *file_name) {
    //stuff
    new->file_log = old->file_log;
    new->file_out = old->file_out;
    new->h_flag = old->h_flag;
    new->hash_alg = old->hash_alg;
    new->o_flag = old->o_flag;
    new->r_flag = old->r_flag;
    new->v_flag = old->v_flag;
    //imp
    new->target = file_name;
}

int dir_write (char **str, defStruct *def) {
    int file;
    int li = 0; 
    int i=0; 

    //count lines
    while (strchr (str[li],','))
        li++;
    
    //subtract 1 bc of trash 
    if (def->o_flag) {
        file = open (def->file_out, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0644);
        if (file == -1) {
            perror (def->file_out);
            return ERROR_FILE_DIR;
        }

        while (i<li) {
            write (file,str[i], strlen(str[i]));
            write (file,"\n",1);
            i++;
        }
         
        return 0;
    } else {
        while (i<li) {
            printf ("%s\n", str[i]);
            i++;
        }

        return 0;
    }
}s