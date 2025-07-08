/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:19:09 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 17:19:10 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newlist;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newlist = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newlist)
		return (NULL);
	while (s1[i])
	{
		newlist[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newlist[i + j] = s2[j];
		j++;
	}
	newlist[i + j] = '\0';
	return (newlist);
}

char	*ft_calloc(int size)
{
	int		i;
	char	*newcalloc;

	i = 0;
	newcalloc = malloc(sizeof(char) * (size));
	if (!newcalloc)
		return (NULL);
	while (i < size)
	{
		newcalloc[i] = 0;
		i++;
	}
	return (newcalloc);
}

int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_erreur(int readfd, char *str)
{
	if (readfd == -1)
		return (free(str), str = NULL, NULL);
	if (readfd == 0 && (str[0] == '\0' || !str))
	{
		if (str)
			return (free(str), str = NULL, NULL);
		return (NULL);
	}
	return (str);
}
