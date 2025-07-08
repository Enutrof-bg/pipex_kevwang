/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:17:37 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/08 10:17:42 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define EXIT 1
# define NOEXIT 0

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h> //for wait()
# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"

typedef struct s_pipe
{
	int	fd[2];
}t_pipe;

typedef struct s_pipex
{
	char	*str;
	char	**envpath;
	char	**tab;
	char	*path;

	int		infd;
	int		outfd;
	int		id1;
	int		nbr_cmd;
	int		nbr_pipe;
	t_pipe	*pipefd;
	int		pos;

	char	*heredoc;
}t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);

//pipex_utlis
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	ft_print_tab(char **tab);

//pipex_path
char	*get_path(char **env);
int		exec(char *arg, char **env);

//pipex_free
void	ft_free_double_tab(char **tab);
void	ft_close(int fd[2], int fd2, int status);
void	ft_free(char **tab1, char **tab2, char *str);

//pipex_cmd_bonus
int		ft_cmd_solo(t_pipex *pipex, char **argv, char **env);
int		ft_cmd_outfd(t_pipex *pipex, char **argv, char **env);
int		ft_cmd_mid(t_pipex *pipex, char **argv, char **env);
int		ft_cmd_infd(t_pipex *pipex, char **argv, char **env);

#endif
