/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:37:30 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/19 16:37:31 by kevwang          ###   ########.fr       */
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

void	cmd1(char **argv, char **env, t_pipex *pipex)
{
	if (pipex->pos == 0)
	{
		if (dup2(pipex->infd, 0) == -1)
			ft_close_all(pipex, EXIT);
	}
	else
	{
		dup2(pipex->pipefd[pipex->pos -1].fd[0], 0);
	}
	// if (dup2(pipex->fd[1], 1) == -1)
	if (dup2(pipex->pipefd[pipex->pos].fd[1], 1) == -1)
		ft_close_all(pipex, EXIT);
	// close(pipex->fd[0]);
	// close(pipex->fd[1]);
	close(pipex->pipefd[pipex->pos].fd[0]);
	close(pipex->pipefd[pipex->pos].fd[1]);
	close(pipex->infd);
	if (exec(argv[pipex->pos +2], env) == -1)
	{
		perror("command not found");
		ft_close_all(pipex, EXIT);
	}
}

void	cmd2(char **argv, char **env, t_pipex *pipex)
{
	printf("pos:%d nbr_cmd:%d\n", pipex->pos, pipex->nbr_cmd-1);
	if (pipex->pos == pipex->nbr_cmd-1)
	{
		if (dup2(pipex->outfd, 1) == -1)
			ft_close_all(pipex, EXIT);
	}
	else
	{
		dup2(pipex->pipefd[pipex->pos].fd[1], 1)
		// dup2(pipex->pipefd[pipex->pos -1].fd[0], 0);
	}
	// if (dup2(pipex->fd[0], 0) == -1)
	if (dup2(pipex->pipefd[pipex->pos -1].fd[0], 0) == -1)
		ft_close_all(pipex, EXIT);
	// close(pipex->fd[1]);
	// close(pipex->fd[0]);
	close(pipex->pipefd[pipex->pos].fd[0]);
	close(pipex->pipefd[pipex->pos].fd[1]);
	close(pipex->outfd);

	if (exec(argv[pipex->pos +2], env) == -1)
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
	if (argc <= 3)
		return (1);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	pipex->infd = -1;
	pipex->outfd = -1;
	pipex->nbr_cmd = argc - 3;
	pipex->nbr_pipe = pipex->nbr_cmd - 1;
	pipex->pos = 0;

	pipex->pipefd = malloc(sizeof(t_pipe) * (pipex->nbr_pipe));
		if (!pipex->pipefd)
			return (perror("pipefd malloc"), 1);

	ft_open_pipe(pipex);

	pipex->infd = open(argv[1], O_RDONLY, 0777);
	if (pipex->infd == -1)
	{
		// ft_close_all(pipex,	EXIT);
	}
	pipex->outfd = open(argv[argc-1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfd == -1)
	{
		// ft_close_all(pipex, EXIT);
	}
	while (pipex->pos < pipex->nbr_cmd -1)
	{
		if (pipe(pipex->fd) == -1)
			return (free(pipex), 1);
		pipex->id1 = fork();
		if (pipex->id1 < 0)
			return (close(pipex->fd[0]), close(pipex->fd[1]), free(pipex), 1);
		if (pipex->id1 == 0)
			cmd1(argv, env, pipex);
		ft_close_pipe(pipex);
		// close(pipex->outfd);
		// wait(NULL);
		pipex->pos++;
	}

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
