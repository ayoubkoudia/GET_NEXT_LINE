/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoudia <akoudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:26:40 by akoudia           #+#    #+#             */
/*   Updated: 2022/12/02 16:08:39 by akoudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_next(char *store)
{
	int		i;
	int		j;
	char	*new_store;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
		return (NULL);
	new_store = (char *)malloc(sizeof(char) * (ft_strlen(store) - i));
	if (!new_store)
		return (NULL);
	i++;
	j = 0;
	while (store[i])
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	return (new_store);
}

char	*gline(char *bigline)
{
	int		i;
	char	*line;

	i = 0;
	if (!bigline[i])
		return (NULL);
	while (bigline[i] && bigline[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (bigline[i] && bigline[i] != '\n')
	{
		line[i] = bigline[i];
		i++;
	}
	if (bigline[i] == '\n')
	{
		line[i] = bigline[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*reads(int fd, char *str)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(str);
			return (0);
		}
		buffer[i] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*tmp;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	save = reads(fd, save);
	if (!save)
		return (NULL);
	tmp = save;
	line = gline(tmp);
	save = save_next(tmp);
	free(tmp);
	return (line);
}

// int main()
// {
// 	int fd;
// 	char *str;

// 	fd = open("file1.txt",O_RDONLY);
// 	while ((str=get_next_line(fd)) && str  != NULL)
// 	{
// 	printf("%s", str);	
// 	}
// }
