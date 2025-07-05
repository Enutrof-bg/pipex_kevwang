/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:06:28 by kevwang           #+#    #+#             */
/*   Updated: 2025/04/25 19:06:29 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_count_word(char *str, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			count++;
			while (str[i] != c && str[i] != '\0')
			{
				i++;
			}
		}
	}
	return (count);
}

static char	*ft_add(char *str, char *src, char c)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && src[i] != c)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_string_malloc(char **new_tab, size_t j, size_t index)
{
	new_tab[index] = malloc(sizeof(char) * (j + 1));
	if (!new_tab[index])
	{
		while (index > 0)
		{
			index--;
			free(new_tab[index]);
		}
		free(new_tab);
		return (NULL);
	}
	return (new_tab);
}

static char	**ft_word_split(char *str, char c, char **new_tab, size_t index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			if (str[i + j] == c || str[i + j] == '\0')
			{
				new_tab = ft_string_malloc(new_tab, j, index);
				if (new_tab == NULL)
					return (NULL);
				new_tab[index] = ft_add(new_tab[index], &str[i], c);
				index++;
				i = i + j;
				j = 0;
			}
			j++;
		}
	}
	return (new_tab);
}

char	**ft_split(char const *s, char c)
{
	char	**new_tab;
	size_t	index;
	size_t	len;

	len = ft_count_word((char *)s, c);
	index = 0;
	if (s == NULL)
		return (NULL);
	new_tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (new_tab == NULL)
		return (NULL);
	new_tab = ft_word_split((char *)s, c, new_tab, index);
	if (!new_tab)
		return (NULL);
	new_tab[len] = 0;
	return (new_tab);
}

/*
int main()
{
	
	// char *tab = NULL;
	// char *tab = "111 22 333 444 55   ";
	char *tab = "HELLO! 111 222 333 444 ";
	char c = ' ';
	char **result = ft_split(tab, c);
	int i = 0;
	int j = 0; 

	if (!(tab))
       	printf("NULL");
    else
        if (!tab[0])
           	printf("ok\n");
	while (result[i])
	{
		while (result[i][j])
		{
			write(1,&result[i][j],1);
			j++;
		}
		free(result[i]);
		j = 0;
		i++;
		write(1,"\n",1);
	}
	free(result);
}
*/

/*
int main(int argc, char **argv)
{
	char c = ' ';
	char **tab;
	int i = 0;
	int j = 0;

	if (argc == 2)
	{
		// printf("count word : %zu\n", ft_count_word(argv[1], c));
		tab = ft_split(argv[1], c);
		if (!(tab))
       		printf("NULL");
    	else
        	if (!tab[0])
           		printf("ok\n");

		while (tab[i])
		{
			while (tab[i][j])
			{
				write(1, &tab[i][j], 1);
				j++;
			}
			free(tab[i]);
			j = 0;
			i++;
			write(1, "\n", 1);
		}
		free(tab);
	}

}
*/