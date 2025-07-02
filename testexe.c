
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(/*int argc, char *argv[]*/)
{

    char *args[3];

    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;

    execve("/bin/ls", args, NULL);
    perror("execve");   /* execve() ne retourne qu'en cas d'erreur */
    exit(EXIT_FAILURE);
}
