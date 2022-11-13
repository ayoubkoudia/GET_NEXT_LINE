/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoudia <akoudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:26:40 by akoudia           #+#    #+#             */
/*   Updated: 2022/11/13 14:38:35 by akoudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

char	*read_to_stash(int fd, char *rest)
{
	int		r;
	char	*buffer;

	r = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			break ;
		buffer[r] = '\0';
		rest = ft_strjoin(rest, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*rest = NULL;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
    rest = read_to_stash(fd, rest);
	if (!buff)
		return (NULL);
    return (line);
}
