/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:52 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 17:18:54 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_return(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	while (j < i)
	{
		newstr[j] = str[j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_str_reste(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i + j] != '\0')
		j++;
	newstr = malloc(sizeof(char) * (j + 1));
	if (!newstr)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		newstr[j] = str[i + j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_read(int fd, char *str)
{	
	char	*temp;
	char	*charread;
	int		readfd;

	charread = ft_calloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!charread)
		return (NULL);
	readfd = read(fd, charread, BUFFER_SIZE);
	while (readfd > 0)
	{
		charread[readfd] = '\0';
		temp = ft_strjoin(str, charread);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		if (ft_check(charread, '\n') == 1)
			break ;
		readfd = read(fd, charread, BUFFER_SIZE);
	}
	free(charread);
	return (ft_erreur(readfd, str));
}

char	*ft_reste(char *str)
{
	char	*temp;

	temp = ft_str_reste(str);
	if (!temp)
		return (NULL);
	free(str);
	str = temp;
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*strreturn;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!str)
	{
		str = ft_calloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
	}
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	strreturn = ft_str_return(str);
	if (!strreturn)
		return (NULL);
	str = ft_reste(str);
	if (!str)
		return (NULL);
	if (str && str[0] == '\0')
		return (free(str), str = NULL, strreturn);
	return (strreturn);
}

//str[0] = '\0'  != 		str = NULL
/*
int main()
{
	// int fd = STDIN_FILENO;
	int fd = open("texte.txt", O_RDONLY);
	if (fd < 0)
	{
		write(1, "Erreur\n",7);
	}

	// printf("%d\n", BUFFER_SIZE);
	// close(fd);

	printf("fd :%d\n", fd);
    char *line;
    int i = 0;
    do {
    	line = get_next_line(fd);
    	printf("[%d] '%s'\n", i++, line);
    	free(line);
	} while (line != NULL);
	line = get_next_line(fd);
    printf("[%d] '%s'\n", i++, line);
    free(line);

	// char *newstr = get_next_line(fd);
	// printf("%s", newstr);
	// free(newstr);

	// //printf("test2");
	// newstr = get_next_line(fd);
	// printf("%s", newstr);
	// free(newstr);

	// //printf("test3");
	// newstr = get_next_line(fd);
	// printf("%s", newstr);
	// free(newstr);

	// //printf("test4");
	// newstr = get_next_line(fd);
	// printf("%s", newstr);
	// free(newstr);
}*/


/*
char	*get_next_line(int fd)
{	
	int readfd;
	char *temp;
	static char *str;
	char *newchar;
	char *newline;
	int i = 0;

	if (fd < 1)
	{
		return (NULL);
	}
	// readfd = 1;
	newchar = ft_calloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!newchar)
		return (NULL);
	// str = ft_calloc(sizeof(char) * 1);
	// if (!str)
	// {
	// 	free(newchar);
	// 	return (NULL);
	// }
	while ((readfd = read(fd, newchar, BUFFER_SIZE)) > 0)
	{
		newchar[readfd] = 0;
		if(str == NULL)
			str = ft_calloc(sizeof(char) * 1);
		temp = ft_strjoin(str , newchar);
		// free(str);
		str = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		if(!str)
		{
			free(newchar);
			free(str);
			return (NULL);
		}
		while (temp[i])
		{
			str[i] = temp[i];
			i++;
		}
		str[ft_strlen(temp)] = '\0';
		free(temp);
		temp = NULL;
		i = 0;
		if (ft_check(str, '\n') == 1 || ((ft_check(str, '\n') == 0 && readfd < 1)))
		{
			
			// printf("result str1:\n%s|fin\n\n", str);
			newline = ft_strchr(str);
			str = ft_str_reste(str);
			// printf("result newline1:%s|fin", newline);
			// printf("result str2:\n%s|fin\n\n", str);
			free(newchar);
			return (newline);
		}
	}
	free(newchar);
	return (str);
}
*/

	// static int size = BUFFER_SIZE;
/*
	printf("size : %d\n" , BUFFER_SIZE);
	char *buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	int readtest = read(fd, buf, BUFFER_SIZE);
	buf[readtest] = '\0';
	printf("readtest : %d\n%s\n", readtest, buf);
*/
	// printf("%s\n", ft_strjoin("bonjour", "123456"));

// save de getnextline avec buffer 1
/*
char	*get_next_line(int fd)
{	
	int readfd;
	char *temp;
	char *str;
	char *newchar;
	int i = 0;

	if (fd < 1)
	{
		return (NULL);
	}
	readfd = 1;
	newchar = ft_calloc(sizeof(char) * 2);
	if (!newchar)
		return (NULL);
	str = ft_calloc(sizeof(char) * 1);
	if (!str)
	{
		free(newchar);
		return (NULL);
	}
	while ((readfd = read(fd, newchar, 1)) > 0)
	{
		// readfd = read(fd, newchar, 1);
		// str = "";
		// printf("%d\n", readfd);
		// printf("%s", newchar);
		// write(1, &newchar[0],1);
		// str = newline;
		// free(newline);
		temp = ft_strjoin(str , newchar);
		free(str);
		// str = temp;
		
		str = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		if(!str)
		{
			free(newchar);
			free(str);
			return (NULL);
		}
		while (temp[i])
		{
			str[i] = temp[i];
			i++;
		}
		str[ft_strlen(temp)] = '\0';
		free(temp);
		temp = NULL;

		i = 0;
		if (newchar[0] == '\n')
			break;
	}
	free(newchar);
	return (str);
}*/