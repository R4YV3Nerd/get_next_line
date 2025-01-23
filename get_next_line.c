/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/24 00:46:03 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff; // buff is used for reading the file descriptor and storing the data read from the file descriptor
	static char		*data;
	ssize_t			readed;
	int				i;

	while (1)
	{
		buff = malloc((size_t)BUFFER_SIZE + 1); // we allocate memory for the buffer with the size of the buffer size + 1 for the null terminator 
		if (fd < 0 || BUFFER_SIZE <= 0 || !buff) // if the file descriptor is invalid, the buffer size is invalid or the buffer is NULL, we return NULL
			return (free(buff), free(data), data = NULL, NULL); // we free the buffer and the data and we set the data to NULL
		readed = read(fd, buff, BUFFER_SIZE); // we read the file descriptor and we store the number of bytes read in readed
		if (readed == -1) // if the read failed, we return NULL
			return (free(buff), free(data), data = NULL, NULL); // we free the buffer and the data and we set the data to NULL
		buff[readed] = '\0'; // we add the null terminator to the buffer at the position readed + 1 (the end of the buffer) to make it a string 
		data = str_join(data, buff); // we join the buffer to the data and we store the result in the data
		if (find_nl(data, &i)) // if we find a newline in the data we extract the data from the start to the newline character and we return it
		{
			buff = str_sub(data, 0, ++i, 0); //  this function is the one responsible for skipping the newline character and returning the substring from the start to the newline character.
			data = str_copy(data, data + i, str_len(data + i)); // we copy the data from i where the newline character is to the end of the data to the data and we return the concatenated string 
			return (buff); // we return the substring
		}
		if (!readed) // if the readed is 0, we reached the end of the file
			return (buff = data, data = NULL, buff); // we set the buffer to the data and the data to NULL and we return the buffer
	}
}