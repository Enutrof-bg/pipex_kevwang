/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:47:33 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/17 11:47:34 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		pipe(pipex->pipefd[i].fd);
		i++;
	}
}

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

	pipex->infd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0777);
	test = get_next_line(0);
	while (test)
	{
		if (ft_strncmp(test, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(test);
			break ;
		}
		write(pipex->infd, test, ft_strlen(test));
		free(test);
		test = get_next_line(0);
	}
	close(pipex->infd);
	if (pipe(pipex->fd) == -1)
		exit(EXIT_FAILURE);
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		pipex->infd = open("temp", O_RDONLY, 0777);
		dup2(pipex->infd, 0);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->infd);
		exec(argv[3], env);
		// close(pipex->fd[1]);
		// close(pipex->infd);
	}
	wait(NULL);
	close(pipex->fd[1]);
	if (argc == 6)
	{
		pipex->id1 = fork();
		if (pipex->id1 == 0)
		{
			pipex->outfd = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(pipex->fd[0], 0);
			dup2(pipex->outfd, 1);
			close(pipex->fd[1]);
			close(pipex->fd[0]);
			close(pipex->outfd);
			exec(argv[4], env);
			// close(pipex->fd[1]);
			// close(pipex->outfd);
		}
		wait(NULL);
	}
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	unlink("temp");
	return (0);
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->pipefd)
		free(pipex->pipefd);
	free(pipex);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **env)
{
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
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if (argc >= 4)
	{
		pipex = malloc(sizeof(t_pipex));
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			ft_here_doc(argc, argv, env, pipex);
			free(pipex);
			return (1);
		}
		// if (pipex_init(pipex, argc, argv, env) == 1)
		// 	return (1);
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
		ft_open_pipe(pipex);
		// pipe(pipex->fd);
		// else
		// {
		// 	dup2(pipex->infd, 0);
		// }
		// while (i < pipex->nbr_cmd)
		// {

		// 	i++;
		// }
		// 

		// if (argc == 4)
		// 	ft_cmd_solo(pipex, argv, env);
		// if (argc > 4)
		// {
		// 	while (pipex->pos++ < pipex->nbr_cmd)
		// 	{
		// 		if (pipex->pos == 0)
		// 			ft_cmd_infd(pipex, argv, env);
		// 		else if (pipex->pos == pipex->nbr_pipe)
		// 			ft_cmd_outfd(pipex, argv, env);
		// 		else
		// 			ft_cmd_mid(pipex, argv, env);
		// 	}
		// }

		// dup2(pipex->infd, 0);

		// exec(argv[pipex->pos+2], env);

		// int tmpin = dup(0);
		// int tmpout = dup(1);

		// int fdin;
		// int fdout;
		// int ret;

		//if
		// fdin = open(argv[1], O_RDONLY);
		//else

		while (pipex->pos < pipex->nbr_cmd)
		{
			pipe(pipex->fd);
			if (pipex->pos == 0)
			{
				dup2(pipex->infd, 0);
				close(pipex->infd);
			}
			else
			{
				dup2(pipex->fd[0], 0);
			}
			if (pipex->pos == pipex->nbr_cmd -1)
			{
				dup2(pipex->outfd, 1);
				close(pipex->outfd);
			}
			else
			{
				dup2(pipex->fd[1], 1);
				close(pipex->fd[1]);
				// dup2(pipex->pipefd)
			}

			int id1 = fork();
			if (id1 == 0)
			{
				// if (pipex->pos > 0)
					// dup2(pipex->pipefd[pipex->pos].fd[0], 0);
				// dup2(pipex->pipefd[pipex->pos].fd[1], 1);
				// ft_close_pipe(pipex);
				// if (pipex->)
				// dup2(pipex->fd[0], 0);
				exec(argv[pipex->pos + 2], env);

				char str[5000];
				int readfd = read(0, str, 5000);
				str[readfd] = 0;
				write(2, str, ft_strlen(str));
			}
			pipex->pos++;
		}
		// // dup2(pipex->outfd, 1);
		// dup2(pipex->pipefd[pipex->pos].fd[0], 0);
		// // ft_close_pipe(pipex);
		// exec(argv[pipex->pos +2], env);
		ft_close_pipe(pipex);
		ft_free_pipex(pipex);
		return (0);
	}
}

/*
void	cmd1(char **argv, char **env, t_pipex *pipex)
{
	pipex->infd = open(argv[1], O_RDONLY, 0777);
	if (pipex->infd == -1)
		ft_close_all(pipex,	EXIT);
	if (dup2(pipex->infd, 0) == -1)
		ft_close_all(pipex, EXIT);
	if (dup2(pipex->fd[1], 1) == -1)
		ft_close_all(pipex, EXIT);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->infd);
	if (exec(argv[2], env) == -1)
	{
		perror("command not found");
		ft_close_all(pipex, EXIT);
	}
}

void	cmd2(char **argv, char **env, t_pipex *pipex)
{
	pipex->outfd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfd == -1)
		ft_close_all(pipex, EXIT);
	if (dup2(pipex->outfd, 1) == -1)
		ft_close_all(pipex, EXIT);
	if (dup2(pipex->fd[0], 0) == -1)
		ft_close_all(pipex, EXIT);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(pipex->outfd);
	if (exec(argv[3], env) == -1)
	{
		perror("command not found");
		ft_close_all(pipex, 127);
	}
}

int	main(int argc, char **argv, char **env)
{

	t_pipex	*pipex;
	int exit_status;

	exit_status = 0;
	(void)exit_status;
	if (argc != 5)
		return (1);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	pipex->infd = -1;
	pipex->outfd = -1;
	if (pipe(pipex->fd) == -1)
		return (free(pipex), 1);
	pipex->id1 = fork();
	if (pipex->id1 < 0)
		return (close(pipex->fd[0]), close(pipex->fd[1]), free(pipex), 1);
	if (pipex->id1 == 0)
		cmd1(argv, env, pipex);
	pipex->id2 = fork();
	if (pipex->id2 < 0)
		return (close(pipex->fd[0]), close(pipex->fd[1]), free(pipex), 1);
	if (pipex->id2 == 0)
		cmd2(argv, env, pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->id1, &pipex->status, 0);
	waitpid(pipex->id2, &pipex->status, 0);
	if (WIFEXITED(pipex->status))
			exit_status = WEXITSTATUS(pipex->status);
	free(pipex);
	return (exit_status);
}
*/
