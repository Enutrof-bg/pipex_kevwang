#include "pipex.h"

int main()
{
	//cat << fin >> outfile
	//commande a faire dans le terminal

/*
	int result;
	char *fichier = "test/text.txt";

	result = access(fichier, F_OK);
	printf("test access:%d\n", result);
	if (result == -1)
	{
		//-1 si erreur
		perror("Error");
	}
*/

/*
	int fd = open("test/text.txt", O_WRONLY | O_CREAT);
	if (fd == -1)
	{
		perror("Error open");
	}
	printf("fd:%d\n", fd);

	dup2(fd, 1); //le stdout est remplacé par fd
	close(fd);
	printf("Bonjour123");//le printf ecrit dans fd (le ficher text.txt)

	// int newfd = dup(fd);
	// printf("newfd:%d\n", newfd);

	// int newfd2 = dup2(newfd, fd);
	// printf("newfd2:%d fd:%d\n", newfd2, fd);
*/

/*
    char *args[3];

    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;

    execve("/bin/ls", args, NULL);
    perror("execve");
*/

}