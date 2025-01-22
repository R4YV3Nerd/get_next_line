/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/26 13:14:22 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FDS 1024  // Adjust this if necessary for the maximum number of FDs you expect

static char *fd_buffers[MAX_FDS] = {0};  // Array to hold buffers for each fd
static size_t fd_positions[MAX_FDS] = {0};  // Positions for each fd

char	*create_empty_string(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

void	move_str_start(char **str, size_t start)
{
	char	*temporary_buffer;

	temporary_buffer = *str;
	*str = extract_substr(*str, start, get_str_len(*str));
	free(temporary_buffer);
}

int	prepare_prev_line(char **stored_data, int fd)
{
	char	*buf;
	ssize_t	ret;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	if (!fd_buffers[fd])  // If no buffer exists for this fd, initialize it
		fd_buffers[fd] = create_empty_string();
	if (!fd_buffers[fd])
		return (0);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = 0;
		fd_buffers[fd] = concat_strings(fd_buffers[fd], buf);
		if (find_character(fd_buffers[fd], '\n') >= 0)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (1);
}

char	*get_next_line(int fd)
{
	int				newline_index;
	char			*readed;

	if (!prepare_prev_line(&fd_buffers[fd], fd))
		return (NULL);
	newline_index = find_character(fd_buffers[fd], '\n');
	if (newline_index >= 0)
	{
		readed = extract_substr(fd_buffers[fd], 0, newline_index + 1);
		move_str_start(&fd_buffers[fd], newline_index + 1);
	}
	else
	{
		readed = extract_substr(fd_buffers[fd], 0, get_str_len(fd_buffers[fd]));
		free(fd_buffers[fd]);
		fd_buffers[fd] = NULL;
	}
	if (get_str_len(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
