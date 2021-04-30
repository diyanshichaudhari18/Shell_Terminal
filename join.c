#include "smallsh.h"
int join(char *com[])
{

    printf("Executing inside join\n");

    //MODIFICATION to handle the commandline
    char **com1 = malloc(256 * sizeof com[0]);
    char **com2 = malloc(256 * sizeof com[0]);

    int i = 0;
    while (i < one)
    {
        com1[i] = com[i];
        i++;
    }
    int j = 0;
    while (j < two)
    {
        com2[j] = com[i + j];
        j++;
    }
    com2[j] = NULL;
    com1[i] = NULL;

    // From here the code is same

    int p[2], status;

    switch (fork())
    {
    case -1:
        perror("1st fork call in join");
        exit(3);
    case 0:
        break;
    default:
        wait(&status);
        return (status);
    }

    //child process's code
    if (pipe(p) == -1)
    {
        perror("pipecall in join ");
        exit(4);
    }

    switch (fork())
    {
    case -1:
        perror("2nd fork call failed in join");
        exit(5);
    case 0:            //the writing process (grandchild procss)
        dup2(p[1], 1); //redirect stdout to the pipe, writing end.
        close(p[0]);
        close(p[1]);
        execvp(com1[0], com1);
        perror("1st execvp call failed in join");
        exit(6);
    default:           //the "parent" process's code
        dup2(p[0], 0); //redirect stdin to the pipe, reading end
        close(p[0]);
        close(p[1]);
        execvp(com2[0], com2);
        perror("2nd execvp call failed in join");
        exit(7);
    }
}