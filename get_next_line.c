/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/07 21:28:38 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_clean(int fd, char *line, char **buffer)
{
	int	ret;

	ret = read(fd, line, (size_t)BUFFER_SIZE);
	if (ret < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	if (ret == 0)
		return (0);
	line[ret] = '\0';
	while (ret > 0)
	{
		*buffer = ft_strjoin(*buffer, line);
		if (ft_clean(line) > 0)
			break ;
		ret = read(fd, line, (size_t)BUFFER_SIZE);
		line[ret] = '\0';
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		line = malloc((size_t)BUFFER_SIZE + 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	buffer = ft_strjoin(0, line);
	if (ft_clean(line) > 0)
		return (buffer);
	if (read_and_clean(fd, line, &buffer) <= 0)
	{
		if (buffer && *buffer != '\0')
		{
			return (free(line), line = NULL, buffer);
		}
		return (free (buffer), free(line), line = NULL, NULL);
	}
	return (buffer);
}
