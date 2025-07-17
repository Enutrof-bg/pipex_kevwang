/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:07:09 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/17 12:07:09 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

