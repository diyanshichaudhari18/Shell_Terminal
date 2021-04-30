#include "smallsh.h"

/**
 * Function to get the current directory,
 * using getcwd() method to implement task 2 
 * i.e. to change  the  prompt  of  the  shell 
 * to current  working  directory followed 
 * by the dollar sign "$"
 * 
 * return dir stream of character 
*/
char *currentDirectory()
{
    long size;
    char *buf;
    char *dir;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        dir = getcwd(buf, (size_t)size);
    return dir;
}

/**
 * Function to get the current directory,
 * using getcwd() method to implement task 2 
 * i.e. to change  the  prompt  of  the  shell 
 * to current  working  directory followed 
 * by the dollar sign "$"
 * 
 * @param **argv : array of string
 * @returns void. 
*/
void changeDirectory(char **argv)
{
    char currentDir[512];
    char *dir = getenv("HOME");

    if (argcc == 1)
    {
        strcpy(currentDir, dir);
    }
    else if (argcc > 2)
    {
        perror("cd: too many arguments");
    }
    else
    {
        strcpy(currentDir, argv[1]);
    }

    if (chdir(currentDir) == -1)
    {
        perror("cd failed");
    }
}