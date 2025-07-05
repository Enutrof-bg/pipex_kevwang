/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:37:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/05 16:37:20 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	char	*str;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			str = env[i];
			str = str + 5;
			return (str);
		}
		i++;
	}
	return (NULL);
}

void ft_free(char **tab1, char **tab2, char *str)
{
	if (tab1)
		ft_free_double_tab(tab1);
	if (tab2)
		ft_free_double_tab(tab2);
	if (str)
		free(str);
	exit(EXIT_FAILURE);
}

char	*check_path(char **tab, char **cmd)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	while (tab[i])
	{
		temp = ft_strjoin(tab[i], "/");
		if (!temp)
		{
			// ft_free_double_tab(cmd);
			// ft_free_double_tab(tab);
			// exit(EXIT_FAILURE);
			ft_free(cmd, tab, NULL);
		}
		temp2 = ft_strjoin(temp, cmd[0]);
		if (!temp2)
		{
			// ft_free_double_tab(cmd);
			// ft_free_double_tab(tab);
			// free(temp);
			// exit(EXIT_FAILURE);
			ft_free(cmd, tab, temp);
		}
		free(temp);
		if (access(temp2, X_OK) == 0)
			return (temp2);
		free(temp2);
		i++;
	}
	return (NULL);
}

void	exec(char *arg, char **env)
{
	char	*str;
	char	**envpath;
	char	**tab;
	char	*path;

	str = get_path(env);
	envpath = ft_split(str, ':');
	if (!envpath)
		exit(EXIT_FAILURE);
	tab = ft_split(arg, ' ');
	if (!tab)
	{
		// ft_free_double_tab(envpath);
		// exit(EXIT_FAILURE);
		ft_free(envpath, NULL, NULL);
	}
	path = check_path(envpath, tab);
	if (!path)
	{
		// ft_free_double_tab(envpath);
		// ft_free_double_tab(tab);
		// exit(EXIT_FAILURE);
		ft_free(envpath, tab, NULL);
	}
	execve(path, tab, env);
	// ft_free_double_tab(envpath);
	// ft_free_double_tab(tab);
	// free(path);
	ft_free(envpath, tab, path);
}
