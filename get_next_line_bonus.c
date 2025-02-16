/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:02:52 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/07 22:52:27 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

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
	static char	*line[FDS_MAX];
	char		*buffer;

	if (fd < 0 || fd >= FDS_MAX || BUFFER_SIZE == 0)
		return (NULL);
	if (!line[fd])
	{
		line[fd] = malloc((size_t)BUFFER_SIZE + 1);
		if (!line[fd])
			return (NULL);
		line[fd][0] = '\0';
	}
	buffer = ft_strjoin(0, line[fd]);
	if (ft_clean(line[fd]) > 0)
		return (buffer);
	if (read_and_clean(fd, line[fd], &buffer) <= 0)
	{
		if (buffer && *buffer != '\0')
			return (buffer);
		return (free(line[fd]), line[fd] = NULL, NULL);
	}
	return (buffer);
}

#include <stdio.h>
int main()
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);
	int fd4 = open("test4.txt", O_RDONLY);

char *line;

	while((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);

		if((line = get_next_line(fd2)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		if((line = get_next_line(fd3)) != NULL)
		{
			printf("%s", line);
			free(line);
		}

		if((line = get_next_line(fd4)) != NULL)
		{
			printf("%s\n", line);
			free(line);
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);

	return 0;
}