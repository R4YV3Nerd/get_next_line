/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/23 23:50:43 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*data[1024];
	ssize_t			readed;
	int				i;

	while (1)
	{
		buff = malloc((size_t)BUFFER_SIZE + 1);
		if (fd < 0 || BUFFER_SIZE <= 0 || !buff)
			return (free(buff), free(data[fd]), data[fd] = NULL, NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), free(data[fd]), data[fd] = NULL, NULL);
		buff[readed] = '\0';
		data[fd] = str_join(data[fd], buff);
		if (find_nl(data[fd], &i))
		{
			buff = str_sub(data[fd], 0, ++i, 0);
			data[fd] = str_copy(data[fd], data[fd] + i, str_len(data[fd] + i));
			return (buff);
		}
		if (!readed)
			return (buff = data[fd], data[fd] = NULL, buff);
	}
}