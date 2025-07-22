/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:24:20 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/05 18:24:21 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free(char **tab1, char **tab2, char *str)
{
	if (tab1)
		ft_free_double_tab(tab1);
	if (tab2)
		ft_free_double_tab(tab2);
	if (str)
		free(str);
}

void	ft_close(int fd[2], int fd2, int exit_val)
{
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
	if (fd2 != -1)
		close (fd2);
	if (exit_val >= 0)
		exit(exit_val);
}

void	ft_close_all(t_pipex *pipex, int exit_val)
{
	ft_close_pipe(pipex);
	if (pipex->infd != -1)
		close(pipex->infd);
	if (pipex->outfd != -1)
		close(pipex->outfd);
	free(pipex->pipefd);
	free(pipex);
	if (exit_val >= 0)
		exit(exit_val);
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->pipefd)
		free(pipex->pipefd);
	free(pipex);
}
