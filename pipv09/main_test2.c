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

#include "pipex_bonus.h"

void	ft_open_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_pipe)
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
		// dup2(pipex->fd[0], 0);
		dup2(pipex->pipefd[pipex->pos -1].fd[0], 0);
	}
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
	// printf("pos:%d nbr_cmd:%d\n", pipex->pos, pipex->nbr_cmd-1);
	if (pipex->pos == pipex->nbr_cmd-1)
	{
		if (dup2(pipex->outfd, 1) == -1)
			ft_close_all(pipex, EXIT);
	}
	else
	{
		// dup2(pipex->fd[1], 1);
		dup2(pipex->pipefd[pipex->pos -1].fd[0], 0);
	}
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
	if (argc < 4)
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
	// pipex->infd = open(argv[1], O_RDONLY, 0777);
	// if (pipex->infd < 0)
	// {
	// 	// return (perror("infile"), 1);
	// 	// ft_close_all(pipex,	EXIT);
	// }
	// pipex->outfd = open(argv[argc-1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// if (pipex->outfd < 0)
	// {
	// 	// ft_close_all(pipex, EXIT);
	// 	// return (perror("outfile"), 1);
	// }
	while (pipex->pos < pipex->nbr_cmd)
	{
		pipex->pipefd[pipex->pos].id1 = fork();
		if (pipex->pipefd[pipex->pos].id1 < 0)
			return (close(pipex->fd[0]), close(pipex->fd[1]), free(pipex), 1);
		if (pipex->pipefd[pipex->pos].id1 == 0)
		{
			if (pipex->nbr_cmd == 1)
			{
				dup2(pipex->infd, 0);
				dup2(pipex->outfd, 1);
			}
			else if (pipex->pos == 0)
			{
				pipex->infd = open(argv[1], O_RDONLY, 0777);
				if (pipex->infd < 0)
				{
					// return (perror("infile"), 1);
					ft_close_all(pipex,	EXIT);
				}
				dup2(pipex->infd, 0);
				dup2(pipex->pipefd[pipex->pos].fd[1], 1);
			}
			else if (pipex->pos == pipex->nbr_cmd -1)
			{
				pipex->outfd = open(argv[argc -1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if (pipex->outfd < 0)
				{
					ft_close_all(pipex, EXIT);
					// return (perror("outfile"), 1);
				}
				dup2(pipex->pipefd[pipex->pos-1].fd[0], 0);
				dup2(pipex->outfd, 1);
			}
			else
			{
				dup2(pipex->pipefd[pipex->pos -1].fd[0], 0);
				dup2(pipex->pipefd[pipex->pos].fd[1], 1);
			}
			ft_close_pipe(pipex);
			if (pipex->infd != -1)
				close(pipex->infd);
			if (pipex->outfd != -1)
				close(pipex->outfd);
			if (exec(argv[pipex->pos +2], env) == -1)
			{
				perror("command not found");
				ft_close_all(pipex, 127);
			}
			free(pipex->pipefd);
			free(pipex);
		}
		pipex->pos++;
	}
	ft_close_pipe(pipex);
	if (pipex->infd != -1)
		close(pipex->infd);
	if (pipex->outfd != -1)
		close(pipex->outfd);
	close(pipex->outfd);
	int j = 0;
	while (j < pipex->nbr_cmd)
	{
		// wait(NULL);
		waitpid(pipex->pipefd[j].id1, &pipex->status, 0);
		j++;
	}
	if (WIFEXITED(pipex->status))
			exit_status = WEXITSTATUS(pipex->status);
	free(pipex->pipefd);
	free(pipex);
	return (exit_status);

}

/*
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

// int	ft_here_doc(int argc, char **argv, char **env, t_pipex *pipex)
// {
// 	char	*test;
// 	char	*temp;

// 	(void)argc;
// 	pipex->heredoc = malloc(sizeof(char) * 1);
// 	if (!pipex->heredoc)
// 		return (-1);
// 	pipex->heredoc[0] = 0;
// 	test = get_next_line(0);
// 	while (test)
// 	{
// 		if (ft_strncmp(test, argv[2], ft_strlen(argv[2])) == 0)
// 		{
// 			break ;
// 		}
// 		temp = ft_strjoin(pipex->heredoc, test);
// 		free(pipex->heredoc);
// 		pipex->heredoc = temp;
// 		free(test);
// 		test = get_next_line(0);
// 	}
// 	pipex->tab = ft_split(pipex->heredoc, '\n');
// 	pipex->id1 = fork();
// 	if (pipex->id1 == 0)
// 	{
// 		pipex->outfd = open(argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		dup2(pipex->outfd, 1);
// 		exec(argv[3], env);
// 		close(pipex->outfd);
// 	}
// 	wait(NULL);
// 	return (0);
// }


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

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		i;

	if (argc >= 4)
	{
		pipex = malloc(sizeof(t_pipex));
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			ft_here_doc(argc, argv, env, pipex);
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
		pipex->pipefd = malloc(sizeof(t_pipe) * (pipex->nbr_pipe));
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
	}
}
*/
