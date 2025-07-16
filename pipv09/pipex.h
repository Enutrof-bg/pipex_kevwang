/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:56:39 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/27 11:56:39 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT 1
# define NOEXIT 0

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h> //for wait()
# include "ft_printf/ft_printf.h"

typedef struct s_pipex
{
	char	*str;
	char	**envpath;
	char	**tab;
	char	*path;

	int		infd;
	int		outfd;
	int		id1;
	int		id2;
	int		fd[2];

	int 	status;
	int		exit_status;
}t_pipex;

char	*get_next_line(int fd);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

//pipex_utlis
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	ft_print_tab(char **tab);

//pipex_path
int		exec(char *arg, char **env);

//pipex_free
void	ft_free_double_tab(char **tab);
void	ft_close(int fd[2], int fd2, int status);
void	ft_free(char **tab1, char **tab2, char *str);
void	ft_close_all(t_pipex *pipex, int exit_val);

#endif
