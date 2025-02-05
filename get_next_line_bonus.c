/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:02:52 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/05 08:02:55 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#ifndef FDS_MAX
# define FDS_MAX 1024
#endif

static int	read_and_clean(int fd, char *line, char **buffer)
{
	int	ret;

	ret = read(fd, line, (size_t)BUFFER_SIZE);
	if (ret < 0)
	{
		free(*buffer);
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
	static char	line[FDS_MAX][BUFFER_SIZE + 1];
	char		*buffer;

	if (fd < 0 || fd >= FDS_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_strjoin(0, line[fd]);
	if (ft_clean(line[fd]) > 0)
		return (buffer);
	if (read_and_clean(fd, line[fd], &buffer) <= 0)
	{
		if (buffer && *buffer != '\0')
			return (buffer);
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
