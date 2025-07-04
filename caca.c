    
#include "pipex.h"

int main(/*int argc, char *argv[]*/)
{

    char *args[3];
    // char test[5000];
    // int readfd;
    int fdop;

    // (void)fdop;
    // (void)test;
    // (void)readfd;

    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;

    // int fd[2];
    // if (pipe(fd) == -1)
        // return 1;
    // printf("tube1:%d tube2:%d\n", tube[0], tube[1]);

    // int id1 = fork();
    // if (id1 == -1)
        // return 1;
   
    fdop = open("infile", O_WRONLY | O_CREAT);
    // (void)fdop;
    // // printf("fd:%d\n", fd);
    dup2(fdop, 1);

    // printf("caca\n");
    // dup2(fd[1], 1);
    // if (id1 == 0)
    // {
        // execlp("ls", "ls", "-l", NULL);
    // int fdopen = open("infile", O_WRONLY | O_CREAT);
        // printf("fd:%d\n", fd);
        // dup2(fd[1], 1);clear
    // dup2(fdopen, 1);
    execve("/bin/ls", args, NULL);
    perror("execve");   /* execve() ne retourne qu'en cas d'erreur */

    // close(fd[1]);
    // readfd = read(fd[0], test, 5000);
    // dup2(1, fd[1]);
    // printf("readfd:%d\n", readfd);
    // printf("'%s'", test);
    // dup2(fd[0] , 0);

    // execve("/bin/wc", args, NULL);
    // perror("execve");   /* execve() ne retourne qu'en cas d'erreur */
        // close(fd[0]);
        // close(fd[1]);
        // exit(EXIT_FAILURE);
    // }

    // int id2 = fork();
    // if (id2 == -1)
        // return 1;

    // if (id2 == 0)
    // {
        // dup2(fd[0], 0);
        // close(fd[0]);
        // close(fd[1]);
    // execlp("grep", "grep", "rtt", NULL);
    // execve("/bin/grep", args, NULL);
        // perror("execve");
       
    // }

    // close(fd[0]);
    // close(fd[1]);

    // wait(NULL);
    // waitpid(id1, NULL, 0);
    // waitpid(id2, NULL, 0);
    return 0;
}
