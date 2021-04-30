#include "smallsh.h"
void redirect(char *com[], int arc) {
    char filename[MAXBUF];
    strcpy(filename,com[arc]);
    com[arc] = NULL;
    
    printf("%s\n",filename);
    int filefd = open(filename, O_WRONLY | O_CREAT, 0666);
    if (!fork())
    {
        close(1); //Close stdout
        dup(filefd);
        execvp(com[0], com);
    }
    else
    {
        close(filefd);
        wait(NULL);
    }
}