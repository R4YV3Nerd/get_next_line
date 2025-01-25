/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/25 22:26:37 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*data;
	ssize_t			readed;
	int				i;

	while (1) 
	{
		buff = malloc((size_t)BUFFER_SIZE + 1);
		if (fd < 0 || BUFFER_SIZE <= 0 || !buff)
			return (free(buff), free(data), data = NULL, NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), free(data), data = NULL, NULL);
		buff[readed] = '\0';
		data = ft_strjoin(data, buff);
		if (find_nl(data, &i))
		{
			buff = sub_str(data, 0, ++i, 0);
			data = str_ncpy(data, data + i, get_len(data + i));
			return (buff);
		}
		if (!readed)
			return (buff = data, data = NULL, buff);
	}
}
