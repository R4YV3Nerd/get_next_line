/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:04:09 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/16 18:11:02 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!(*stored_data))
		*stored_data = create_empty_string();
	if (!(*stored_data))
		return (0);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = 0;
		*stored_data = concat_strings(*stored_data, buf);
		if (find_character(*stored_data, '\n') >= 0)
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
	static char		*stored_data = NULL;

	if (!prepare_prev_line(&stored_data, fd))
		return (NULL);
	newline_index = find_character(stored_data, '\n');
	if (newline_index >= 0)
	{
		readed = extract_substr(stored_data, 0, newline_index + 1);
		move_str_start(&stored_data, newline_index + 1);
	}
	else
	{
		readed = extract_substr(stored_data, 0, get_str_len(stored_data));
		free(stored_data);
		stored_data = NULL;
	}
	if (get_str_len(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
