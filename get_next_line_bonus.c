/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/02 21:44:53 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef FDS_MAX
# define FDS_MAX 1024
#endif

static int	read_and_clean(int fd, char *line, char **next_line)
{
	int	ret;

	ret = read(fd, line, BUFFER_SIZE);
	if (ret < 0)
	{
		free(*next_line);
		return (-1);
	}
	if (ret == 0)
		return (0);
	line[ret] = '\0';
	while (ret > 0)
	{
		*next_line = ft_strjoin(*next_line, line);
		if (ft_clean(line) > 0)
			break ;
		ret = read(fd, line, BUFFER_SIZE);
		line[ret] = '\0';
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	line[FDS_MAX][BUFFER_SIZE + 1];
	char		*next_line;

	if (fd < 0 || fd >= FDS_MAX || BUFFER_SIZE < 1)
		return (NULL);
	next_line = ft_strjoin(0, line[fd]);
	if (ft_clean(line[fd]) > 0)
		return (next_line);
	if (read_and_clean(fd, line[fd], &next_line) < 0)
	{
		free(next_line);
		return (NULL);
	}
	if (next_line && *next_line == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
