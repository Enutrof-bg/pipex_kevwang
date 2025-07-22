/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:43:51 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/22 16:43:52 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->pipefd[i].fd) == -1)
			return (1);
		i++;
	}
	return (0);
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

void	ft_waitpid(t_pipex *pipex)
{
	int	j;

	j = 0;
	while (j < pipex->nbr_cmd)
	{
		waitpid(pipex->pipefd[j].id1, &pipex->status, 0);
		j++;
	}
}

int	ft_dup(int fd0, int fd1)
{
	if (dup2(fd0, 0) == -1)
		return (-1);
	if (dup2(fd1, 1) == -1)
		return (-1);
	return (0);
}
