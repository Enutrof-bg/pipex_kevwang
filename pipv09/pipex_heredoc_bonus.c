/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:42:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/22 16:42:16 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_write_here_doc(t_pipex *pipex, char **argv)
{
	char	*test;

	pipex->infd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
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
}

void	ft_commande1(t_pipex *pipex, char **argv, char **env)
{
	pipex->infd = open("temp", O_RDONLY, 0644);
	ft_dup(pipex->infd, pipex->fd[1]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->infd);
	exec(argv[3], env);
}

void	ft_commande2(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->outfd = open(argv[argc -1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_dup(pipex->fd[0], pipex->outfd);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(pipex->outfd);
	exec(argv[4], env);
}

int	ft_here_doc(int argc, char **argv, char **env, t_pipex *pipex)
{
	ft_write_here_doc(pipex, argv);
	if (pipe(pipex->fd) == -1)
		exit(EXIT_FAILURE);
	pipex->id1 = fork();
	if (pipex->id1 == 0)
		ft_commande1(pipex, argv, env);
	wait(NULL);
	close(pipex->fd[1]);
	if (argc == 6)
	{
		pipex->id1 = fork();
		if (pipex->id1 == 0)
			ft_commande2(pipex, argc, argv, env);
		wait(NULL);
	}
	close(pipex->fd[0]);
	unlink("temp");
	free(pipex);
	return (0);
}
