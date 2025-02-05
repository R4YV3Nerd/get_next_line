/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/05 11:01:10 by maitoumg         ###   ########.fr       */
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
	static char	line[BUFFER_SIZE + 1];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_strjoin(0, line);
	if (ft_clean(line) > 0)
		return (buffer);
	if (read_and_clean(fd, line, &buffer) < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
