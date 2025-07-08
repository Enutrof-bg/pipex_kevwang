/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:12 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/08 12:32:13 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_cmd_infd(t_pipex *pipex, char **argv, char **env)
{
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		dup2(pipex->infd, 0);
		dup2(pipex->pipefd[pipex->pos].fd[1], 1);
		close(pipex->pipefd[pipex->pos].fd[0]);
		exec(argv[pipex->pos + 2], env);
		close(pipex->pipefd[pipex->pos].fd[1]);
		close(pipex->infd);
	}
	wait(NULL);
	close(pipex->pipefd[pipex->pos].fd[1]);
	return (0);
}

int	ft_cmd_mid(t_pipex *pipex, char **argv, char **env)
{
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		dup2(pipex->pipefd[pipex->pos - 1].fd[0], 0);
		dup2(pipex->pipefd[pipex->pos].fd[1], 1);
		close(pipex->pipefd[pipex->pos].fd[0]);
		exec(argv[pipex->pos + 2], env);
		close(pipex->pipefd[pipex->pos].fd[1]);
	}
	wait(NULL);
	close(pipex->pipefd[pipex->pos].fd[1]);
	return (0);
}

int	ft_cmd_outfd(t_pipex *pipex, char **argv, char **env)
{
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		dup2(pipex->pipefd[pipex->pos - 1].fd[0], 0);
		dup2(pipex->outfd, 1);
		close(pipex->pipefd[pipex->pos].fd[0]);
		exec(argv[pipex->pos + 2], env);
		close(pipex->pipefd[pipex->pos].fd[1]);
	}
	wait(NULL);
	close(pipex->pipefd[pipex->pos].fd[1]);
	return (0);
}

int	ft_cmd_solo(t_pipex *pipex, char **argv, char **env)
{
	pipex->id1 = fork();
	if (pipex->id1 == 0)
	{
		dup2(pipex->infd, 0);
		dup2(pipex->outfd, 1);
		close(pipex->pipefd[pipex->pos].fd[0]);
		exec(argv[pipex->pos + 2], env);
		close(pipex->pipefd[pipex->pos].fd[1]);
	}
	wait(NULL);
	close(pipex->pipefd[pipex->pos].fd[1]);
	return (0);
}
