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

char *get_path(char **env)
{
	char *str;
    int i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH", 4) == 0)
        {
        	str = env[i];
        	str = str+5;
        	return (str);
        }
        i++;
    }
    return (NULL);
}

char *check_path(char **tab, char *cmd)
{
	int i = 0;
	char *temp;
	char *temp2;
	while (tab[i])
	{
		temp = ft_strjoin(tab[i], "/");
		temp2 = ft_strjoin(temp, cmd);
		if (access(temp2, X_OK) == 0)
			return (temp2);
		i++;
	}
	return (NULL);
}

void exec(char *arg, char **env)
{
	char *str = get_path(env);
	// printf("%s\n", str);
	char **envpath = ft_split(str, ':');
	// ft_print_tab(envpath);

	char **tab = ft_split(arg, ' ');
	char *path = check_path(envpath, tab[0]);
	printf("path:%s\n", path);
	if (!path)
		exit(EXIT_FAILURE);
	execve(path, tab, env);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;

    // exec("ls -l", env);
    // ft_print_tab(env);
    if (argc == 5)
    {
	    int fd[2];
		pipe(fd);//if == -1

	    int id1 = fork(); // if id1 == -1


	    if (id1 == 0)
	    {
	    	// int infd = open("infile", O_WRONLY | O_CREAT, 0777);
	      	int infd = open(argv[1], O_RDONLY | O_CREAT, 0777);
	    	dup2(infd, 0);
	    	dup2(fd[1], 1);

	    	close(fd[0]);
	    	// char *cmd1 = ft_split(argv[2], " ");
	    	exec(argv[2], env);
	    
	    	close(fd[1]);
	    	// exec("shuf -i 1-10 -n 5", env);
	    }
	    else
	    {
	    	int outfd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	    	// int outfd = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0777);

	    	dup2(outfd, 1);
	    	dup2(fd[0], 0);

	    	// char newread[50000];
	    	// int readfd = read(fd[0], newread, 50000);
	    	// newread[readfd] = 0;
	    	// printf("%s\n", newread);

	    	// exec("grep kev", env);
	    	// wait(NULL);
	    	// printf("tet=st");
	    	

	    	close(fd[1]);
	    	// exec("wc -l", env);
	    	exec(argv[3], env);
	    	close(fd[0]);
	    	// wait(NULL);
	    	// exec("wc -m", env);
	    	
	    	// wait();
	    	
	    }
	}
	return (0);
    // exec("", env);



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
}


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