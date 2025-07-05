/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:56:29 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/27 11:56:30 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1(char **argv, char **env, int fd[2])
{
	int	infd;
	// printf("cmd1||fd0:%d fd1:%d\n", fd[0], fd[1]);
	infd = open(argv[1], O_RDONLY, 0777);
	if (infd == -1)
		ft_close(fd, -1, EXIT);
	if (dup2(infd, 0) == -1)
		ft_close(fd, infd, EXIT);
	if (dup2(fd[1], 1) == -1)
		ft_close(fd, infd, EXIT);
	close(fd[0]);
	if (exec(argv[2], env) == -1)
		ft_close(fd, infd, EXIT);
	// close(infd);
	// ft_close(fd, infd, NOEXIT);
	close(fd[1]);
	// close(fd[0]);
}

void	cmd2(char **argv, char **env, int fd[2])
{
	int	outfd;
	// printf("cmd2||fd0:%d fd1:%d\n", fd[0], fd[1]);
	outfd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (outfd == -1)
		ft_close(fd, -1, EXIT);
	if (dup2(outfd, 1) == -1)
		ft_close(fd, outfd, EXIT);
	if (dup2(fd[0], 0) == -1)
		ft_close(fd, outfd, EXIT);
	close(fd[1]);
	if (exec(argv[3], env) == -1)
		ft_close(fd, outfd, EXIT);
	// close(outfd);
	// close(fd[1]);
	close(fd[0]);
	// ft_close(fd, outfd, NOEXIT);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	id1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		// printf("main||fd0:%d fd1:%d\n", fd[0], fd[1]);
		id1 = fork();
		if (id1 == -1)
			ft_close(fd, -1, EXIT);
		if (id1 == 0)
		{
			cmd1(argv, env, fd);
		}
		else
		{
			cmd2(argv, env, fd);
		}
		// ft_close(fd, -1, NOEXIT);
		// close(fd[0]);
		// close(fd[1]);
	}
	return (0);
}

/*
    if (argc == 5)
    {
	    int fd[2];
	    pipe(fd);

	    int id1 = fork();
	    if (id1 == 0)
	    {
	    	int infd = open(argv[1], O_RDONLY | O_CREAT, 0777);
	    	dup2(infd, 0);
	    	dup2(fd[1], 1);
	    	// close(fd[0]);
	    	exec(argv[2], env);
	    }
	    else 
	    {
	    	int outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	    	dup2(outfd, 1);
	    	dup2(fd[0], 0);
	    	// close(fd[1]);
	    	exec(argv[3], env);
	    	wait(NULL);
	    }
	}
	*/

/*
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int arr[] = {1,2,3,4,5,6,7,8};
	int size = sizeof(arr) / sizeof(int);
	int start;
	int end;
	int fd[2];

	if (pipe(fd) == -1)
		return 1;
	printf("fd1:%d fd2:%d\n", fd[0], fd[1]);
	int id1 = fork();
	if (id1 == -1)
		return 1;

	if (id1 == 0)
	{
		start = 0;
		end = size / 2;
	}
	else 
	{
		start = size/2;
		end = size;
	}
	int sum = 0;
	int i = start;
	wait(NULL);
	while (i < end)
	{
		sum = sum + arr[i];
		printf("i:%d sum:%d\n", i, sum);
		i++;
	}
	if (id1 == 0)
	{
		printf("child sum:%d\n", sum);
		write(fd[1], &sum, sizeof(sum));
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		int sumfromchild;
		read(fd[0], &sumfromchild, sizeof(sumfromchild));
		printf("parent sumfromchild:%d\n", sumfromchild);
		close(fd[0]);
		close(fd[1]);

		int total = sum + sumfromchild;
		printf("total:%d\n", total);
		wait(NULL);
	}
	
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			printf("Process 4 id1:%d id2:%d\n", id1, id2);
		}
		else
		{
			printf("Process 2 id1:%d id2:%d\n", id1, id2);
		}
	}
	else
	{
		if (id2 == 0)
		{
			printf("Process 3 id1:%d id2:%d\n", id1, id2);
		}
		else
		{
			printf("Process 1 id1:%d id2:%d\n", id1, id2);
		}
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		printf("Waiting child to finish.\n");
	}
	
	// printf("id:%d\n", id1);
	// printf("id:%d\n", id2);
	return (0);
}
*/