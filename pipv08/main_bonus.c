/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:17:51 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/08 10:17:52 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_pipe)
	{
		close(pipex->pipefd[i].fd[0]);
		close(pipex->pipefd[i].fd[1]);
		i++;
	}
}

int	ft_here_doc(int argc, char **argv, char **env, t_pipex *pipex)
{
	char	*test;
	char	*temp;

	(void)env;
	(void)temp;
	(void)argc;
	pipex->heredoc = malloc(sizeof(char) * 1);
	if (!pipex->heredoc)
		return (-1);
	pipex->heredoc[0] = 0;

	pipex->infd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0777);
	// dup2(pipex->infd, 1);

	test = get_next_line(0);
	while (test)
	{
		if (ft_strncmp(test, argv[2], ft_strlen(argv[2])) == 0)
		{
			break ;
		}
		write(pipex->infd, test, ft_strlen(test));
		// temp = ft_strjoin(pipex->heredoc, test);
		// free(pipex->heredoc);
		// pipex->heredoc = temp;
		// free(test);
		test = get_next_line(0);
	}
	close(pipex->infd);
	// pipex->tab = ft_split(pipex->heredoc, '\n');
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		pipex->infd = open("temp", O_RDONLY, 0777);
		pipex->outfd = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);

		dup2(pipex->infd, 0);
		dup2(pipex->outfd, 1);
		exec(argv[3], env);
		close(pipex->outfd);
		close(pipex->infd);
	}
	wait(NULL);
	if (argc == 6)
	{
		pipex->id1 = fork();
		if (pipex->id1 == 0)
		{
			pipex->infd = open("temp", O_RDONLY, 0777);
			pipex->outfd = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);

			dup2(pipex->infd, 0);
			// dup2(pipex->outfd, 1);
			exec(argv[4], env);
			close(pipex->outfd);
			close(pipex->infd);
		}
	}
	wait(NULL);
	unlink("temp");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		i;

	if (argc >= 4)
	{
		pipex = malloc(sizeof(t_pipex));
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			if (ft_here_doc(argc, argv, env, pipex) == -1)
				return (free(pipex), 1);
			return (0);
		}
		pipex->str = get_path(env);
		pipex->infd = open(argv[1], O_RDONLY, 0777);
		if (pipex->infd == -1)
			return (perror("infd:"), 1);
		pipex->outfd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->outfd == -1)
			return (perror("outfd:"), 1);
		pipex->nbr_cmd = argc - 3;
		pipex->nbr_pipe = pipex->nbr_cmd - 1;
		pipex->pos = 0;
		pipex->pipefd = malloc(sizeof(t_pipe) * (pipex->nbr_pipe + 1));
		if (!pipex->pipefd)
			return (perror("pipefd malloc"), 1);
		i = 0;
		while (i < pipex->nbr_cmd)
		{
			pipe(pipex->pipefd[i].fd);
			i++;
		}
		if (argc == 4)
		{
			ft_cmd_solo(pipex, argv, env);
		}
		if (argc > 4)
		{
			while (pipex->pos < pipex->nbr_cmd)
			{
				if (pipex->pos == 0)
				{
					ft_cmd_infd(pipex, argv, env);
				}
				else if (pipex->pos == pipex->nbr_pipe)
				{
					ft_cmd_outfd(pipex, argv, env);
				}
				else
				{
					ft_cmd_mid(pipex, argv, env);
				}
				pipex->pos++;
			}
		}
		ft_close_pipe(pipex);
		free(pipex->pipefd);
		free(pipex);
	}
}

// 	if (argc >= 6)
// 	{
// /*
// 		int fd0[2];
// 		int id0;
// 		pipe(fd0);
// 		id0 = fork();
// 		if (id0 == 0)
// 		{
// 			int infd = open(argv[1], O_RDONLY, 0777);
// 			dup2(infd, 0);
// 			dup2(fd0[1], 1);
// 			close(fd0[0]);
// 			exec(argv[2], env);
// 			close(fd0[1]);
// 			close(infd);
// 		}
// 		wait(NULL);
// 		close(fd0[1]);
// 		int fd1[2];
// 		int id1;
// 		pipe(fd1);
// 		id1 = fork();
// 		if (id1 == 0)
// 		{
// 			dup2(fd0[0], 0);
// 			dup2(fd1[1], 1);
// 			close(fd0[1]);
// 			exec(argv[3], env);
// 			close(fd1[0]);
// 		close(fd0[0]);
// 		// close(fd0[1]);
// 		// close(fd1[0]);
// 		close(fd1[1]);
// 		}
// 		wait(NULL);
// 		close(fd1[1]);
// 		int fd2[2];
// 		int id2;
// 		pipe(fd2);
// 		id2 = fork();
// 		if (id2 == 0)
// 		{
// 			dup2(fd1[0], 0);
// 			dup2(fd2[1], 1);
// 			close(fd1[1]);
// 			exec(argv[4], env);
// 			close(fd2[0]);
// 		close(fd0[0]);
// 		close(fd0[1]);
// 		// close(fd1[0]);
// 		close(fd1[1]);
// 		// close(fd2[0]);
// 		close(fd2[1]);
// 		}
// 		wait(NULL);
// 		close(fd2[1]);
// 		int fd3[2];
// 		int id3;
// 		pipe(fd3);
// 		id3 = fork();
// 		if (id3 == 0)
// 		{
// 			int outfd = open(argv[argc - 1],
// 			O_WRONLY | O_TRUNC | O_CREAT, 0777);
// 			dup2(fd2[0], 0);
// 			dup2(outfd, 1);
// 			close(fd2[1]);
// 			exec(argv[5], env);
// 			close(fd3[0]);
// 		close(fd0[0]);
// 		close(fd0[1]);
// 		close(fd1[0]);
// 		close(fd1[1]);
// 		// close(fd2[0]);
// 		close(fd2[1]);
// 		// close(fd3[0]);
// 		close(fd3[1]);
// 		close(outfd);
// 		}
// 		wait(NULL);
// 		close(fd0[0]);
// 		close(fd0[1]);
// 		close(fd1[0]);
// 		close(fd1[1]);
// 		close(fd2[0]);
// 		close(fd2[1]);
// 		close(fd3[0]);
// 		close(fd3[1]);
// */

// 		/*
// 		int fd0[2];

// 		pipe(fd0);
// 		id1 = fork();	
// 		if (id1 == 0)
// 		{
// 			pipe(fd);
// 			id2 = fork();
// 			if (id2 == 0)
// 			{
// 				int id3;
// 				int fd2[2];

// 				pipe(fd2);
// 				id3 = fork();
// 				if (id3 == 0)
// 				{
// 					int infd = open(argv[1], O_RDONLY, 0777);
// 					dup2(infd, 0);
// 					dup2(fd2[1], 1);
// 					close(fd2[0]);
// 					exec(argv[2], env);
// 					close(fd2[1]);
// 				}
// 				else
// 				{
// 					wait(NULL);
// 					dup2(fd2[0], 0);
// 					dup2(fd[1], 1);
// 					close(fd2[1]);
// 					exec(argv[3], env);
// 					close(fd2[0]);
// 				}
// 			}
// 			else
// 			{
// 				wait(NULL);
// 				dup2(fd[0], 0);
// 				dup2(fd0[1], 1);
// 				close(fd[1]);
// 				exec(argv[4], env);
// 				close(fd[0]);
// 			}
// 			close(fd[1]);
// 			close(fd[0]);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			int openfd = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 			dup2(fd0[0], 0);
// 			dup2(openfd, 1);
// 			close(fd0[1]);
// 			exec(argv[5], env);
// 			close(fd0[0]);
// 		}
// 		close(fd0[0]);
// 		close(fd0[1]);
// 		*/
// 	}

// 	return (0);
// 	}

// /*
//     if (argc == 5)
//     {
// 	    int fd[2];
// 	    pipe(fd);

// 	    int id1 = fork();
// 	    if (id1 == 0)
// 	    {
// 	    	int infd = open(argv[1], O_RDONLY | O_CREAT, 0777);
// 	    	dup2(infd, 0);
// 	    	dup2(fd[1], 1);
// 	    	// close(fd[0]);
// 	    	exec(argv[2], env);
// 	    }
// 	    else 
// 	    {
// 	    	int outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	    	dup2(outfd, 1);
// 	    	dup2(fd[0], 0);
// 	    	// close(fd[1]);
// 	    	exec(argv[3], env);
// 	    	wa/it(NULL);
// 	    }
// 	}
// 	*/

// /*
// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	int arr[] = {1,2,3,4,5,6,7,8};
// 	int size = sizeof(arr) / sizeof(int);
// 	int start;
// 	int end;
// 	int fd[2];
// 	if (pipe(fd) == -1)
// 		return 1;
// 	printf("fd1:%d fd2:%d\n", fd[0], fd[1]);
// 	int id1 = fork();
// 	if (id1 == -1)
// 		return 1;
// 	if (id1 == 0)
// 	{
// 		start = 0;
// 		end = size / 2;
// 	}
// 	else 
// 	{
// 		start = size/2;
// 		end = size;
// 	}
// 	int sum = 0;
// 	int i = start;
// 	wait(NULL);
// 	while (i < end)
// 	{
// 		sum = sum + arr[i];
// 		printf("i:%d sum:%d\n", i, sum);
// 		i++;
// 	}
// 	if (id1 == 0)
// 	{
// 		printf("child sum:%d\n", sum);
// 		write(fd[1], &sum, sizeof(sum));
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		int sumfromchild;
// 		read(fd[0], &sumfromchild, sizeof(sumfromchild));
// 		printf("parent sumfromchild:%d\n", sumfromchild);
// 		close(fd[0]);
// 		close(fd[1]);
// 		int total = sum + sumfromchild;
// 		printf("total:%d\n", total);
// 		wait(NULL);
// 	}
// 	int id1 = fork();
// 	int id2 = fork();
// 	if (id1 == 0)
// 	{
// 		if (id2 == 0)
// 		{
// 			printf("Process 4 id1:%d id2:%d\n", id1, id2);
// 		}
// 		else
// 		{
// 			printf("Process 2 id1:%d id2:%d\n", id1, id2);
// 		}
// 	}
// 	else
// 	{
// 		if (id2 == 0)
// 		{
// 			printf("Process 3 id1:%d id2:%d\n", id1, id2);
// 		}
// 		else
// 		{
// 			printf("Process 1 id1:%d id2:%d\n", id1, id2);
// 		}
// 	}
// 	while (wait(NULL) != -1 || errno != ECHILD)
// 	{
// 		printf("Waiting child to finish.\n");
// 	}
// 	// printf("id:%d\n", id1);
// 	// printf("id:%d\n", id2);
// 	return (0);
// }
// */
