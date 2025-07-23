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
			return (NULL);
		temp2 = ft_strjoin(temp, cmd[0]);
		if (!temp2)
			return (free(temp), NULL);
		free(temp);
		if (access(temp2, X_OK) == 0)
			return (temp2);
		free(temp2);
		i++;
	}
	return (NULL);
}

char	*ft_str_last(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	while (str[i - j] != '/' && j < i)
		j++;
	if (str[i - j] == '/')
		j--;
	return (&str[i - j]);
}

int	exec(char *arg, char **env)
{
	char	*str;
	char	**envpath;
	char	**tab;
	char	*path;

	tab = ft_split(arg, ' ');
	if (!tab)
		return (-1);
	if (tab[0][0] == '/' || (tab[0][0] == '.' && tab[0][1] == '/'))
	{
		if (access(tab[0], X_OK) == -1)
			return (ft_free_double_tab(tab), -1);
		if (execve(tab[0], tab, env) == -1)
			return (ft_free_double_tab(tab), -1);
		ft_free_double_tab(tab);
		return (0);
	}
	str = get_path(env);
	if (str)
	{
		envpath = ft_split(str, ':');
		if (!envpath)
			return (ft_free_double_tab(tab), -1);
		// arg = ft_str_last(arg);
		path = check_path(envpath, tab);
		if (!path)
			return (ft_free(envpath, tab, NULL), -1);
		if (execve(path, tab, env) == -1)
		{
			perror("command not found");
			return (ft_free(envpath, tab, path), -1);
		}
		ft_free(envpath, tab, path);
	}
	ft_free_double_tab(tab);
	return (0);
}
