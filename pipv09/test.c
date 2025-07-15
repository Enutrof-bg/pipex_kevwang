#include "pipex.h"

int main()
{
	int status;
	int exit_status = 0;
	int id1 = fork();

	if (id1 == 0)
	{
		printf("test\n");
		exit(127);
	}
	waitpid(id1, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("exit_status:%d\n", exit_status);
	}

	printf("status:%d\n", status);
	return (exit_status);
}