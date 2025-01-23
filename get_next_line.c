/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/23 20:06:32 by maitoumg         ###   ########.fr       */
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
		buff = malloc((size_t)BUFFER_SIZE + 1); // we allocate memory for the buffer
		if (fd < 0 || BUFFER_SIZE <= 0 || !buff) // if the file descriptor is invalid, the buffer size is invalid or the buffer is NULL, we return NULL
			return (free(buff), free(data), data = NULL, NULL); // we free the buffer and the data and we set the data to NULL
		readed = read(fd, buff, BUFFER_SIZE); // we read the file descriptor and we store the number of bytes read in readed
		if (readed == -1) // if the read failed, we return NULL
			return (free(buff), free(data), data = NULL, NULL); // we free the buffer and the data and we set the data to NULL
		buff[readed] = '\0'; // we add the null terminator to the buffer
		data = str_join(data, buff); // we join the buffer to the data
		{
			buff = str_sub(data, 0, ++i, 0); // we create a substring of the data from 0 to i
			data = str_copy(data, data + i, str_len(data + i)); // we copy the data from i to the end of the data
			return (buff); // we return the substring
		}
		if (!readed) // if the readed is 0, we reached the end of the file
			return (buff = data, data = NULL, buff); // we set the buffer to the data and the data to NULL and we return the buffer
	}
}
