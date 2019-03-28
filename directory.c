#include "directory.h"

int dir_read(defStruct *def)
{
    DIR *dir;
    struct dirent *dentry;
    //open dir
    if ((dir = opendir(def->target)) == NULL)
    {
        perror(def->target);
        return ERROR_OPEN;
    }
    //output files
    while ((dentry = readdir(dir)) != NULL)
    {
        //ignore dots

        if (strcmp(dentry->d_name, ".") && strcmp(dentry->d_name, ".."))
        {
            //TODO check if it's a subfolder fork()
                file_finder(def,dentry->d_name);
                file_read(def, dentry->d_name);
        }
    }

    return 0;
}