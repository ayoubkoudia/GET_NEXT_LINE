/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoudia <akoudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:30:49 by akoudia           #+#    #+#             */
/*   Updated: 2022/12/03 12:55:38 by akoudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_next(char *bigline)
{
	int		i;
	int		j;
	char	*new_store;

	i = 0;
	while (bigline[i] && bigline[i] != '\n')
		i++;
	if (!bigline[i])
		return (NULL);
	new_store = (char *)malloc(sizeof(char) * (ft_strlen(bigline) - i));
	if (!new_store)
		return (NULL);
	i++;
	j = 0;
	while (bigline[i])
		new_store[j++] = bigline[i++];
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
	static char	*save[OPEN_MAX];
	char		*tmp;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = reads(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	tmp = save[fd];
	line = gline(tmp);
	save[fd] = save_next(tmp);
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
