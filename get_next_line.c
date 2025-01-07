/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:04:09 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/07 02:04:11 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_empty_string(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

void	shiftstr(char **str, size_t start)
{
	char	*tmp;

	tmp = *str;
	*str = substring(*str, start, string_length(*str));
	free(tmp);
}

int	get_prev(char **previous, int fd)
{
	char	*buf;
	ssize_t	ret;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	if (!(*previous))
		*previous = init_empty_string();
	if (!(*previous))
		return (0);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = 0;
		*previous = string_join(*previous, buf);
		if (find_char(*previous, '\n') >= 0)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (1);
}

char	*get_next_line(int fd)
{
	int				cur;
	char			*readed;
	static char		*previous = NULL;

	if (!get_prev(&previous, fd))
		return (NULL);
	cur = find_char(previous, '\n');
	if (cur >= 0)
	{
		readed = substring(previous, 0, cur + 1);
		shiftstr(&previous, cur + 1);
	}
	else
	{
		readed = substring(previous, 0, string_length(previous));
		free(previous);
		previous = NULL;
	}
	if (string_length(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
