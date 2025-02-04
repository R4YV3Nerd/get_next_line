/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/04 12:47:24 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_clean(int fd, char *line, char **buffer) // this function reads and
{
	int	ret;

	ret = read(fd, line, (size_t)BUFFER_SIZE); // we store what we read in the line buffer
	if (ret < 0)
	{
		free(*buffer);
		return (-1);
	}
	if (ret == 0)
		return (0);
	line[ret] = '\0'; 
	while (ret > 0) // this while loop reads the file and copies it into the buffer until a newline is found and 
	{
		*buffer = ft_strjoin(*buffer, line); // we append the line that we read to the buffer
		if (ft_clean(line) > 0)
			break ;
		ret = read(fd, line, (size_t)BUFFER_SIZE);
		line[ret] = '\0'; // we add a null terminator to the end of the line
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	line[(size_t)BUFFER_SIZE + 1];
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
