/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/25 11:33:12 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// char	*get_next_line(int fd)
// {
// 	char			*buff;
// 	static char		*data;
// 	ssize_t			readed;
// 	int				i;

// 	while (1)
// 	{
// 		buff = malloc((size_t)BUFFER_SIZE + 1);
// 		if (fd < 0 || BUFFER_SIZE <= 0 || !buff)
// 			return (free(buff), free(data), data = NULL, NULL);
// 		readed = read(fd, buff, BUFFER_SIZE);
// 		if (readed == -1)
// 			return (free(buff), free(data), data = NULL, NULL);
// 		buff[readed] = '\0';
// 		data = str_join(data, buff);
// 		if (find_nl(data, &i))
// 		{
// 			buff = str_sub(data, 0, ++i, 0);
// 			data = str_copy(data, data + i, str_len(data + i));
// 			return (buff);
// 		}
// 		if (!readed)
// 			return (buff = data, data = NULL, buff);
// 	}
// }

#include "get_next_line.h"

static char *read_and_append(int fd, char *data) // we create a function that reads the file descriptor and appends the data to the data

{
    char    *buff;
    ssize_t readed;

    buff = malloc((size_t)BUFFER_SIZE + 1);
    if (!buff)
        return (NULL);
    readed = read(fd, buff, BUFFER_SIZE);
    if (readed == -1)
    {
        free(buff);
        return (NULL);
    }
    buff[readed] = '\0';
    data = str_join(data, buff);
    free(buff);
    return (data);
}

static char *extract_line(char **data) // we create a function that extracts the line from the data
{
    char *line;
    int  i;

    if (find_nl(*data, &i))
    {
        line = str_sub(*data, 0, ++i, 0);
        *data = str_copy(*data, *data + i, str_len(*data + i));
        return (line);
    }
    return (NULL);
}

char *get_next_line(int fd) // we create the get_next_line function
{
    static char *data;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (data)
        {
            line = extract_line(&data);
            if (line)
                return (line);
        }
        data = read_and_append(fd, data);
        if (!data)
            return (NULL);
        if (!*data)
        {
            free(data);
            data = NULL;
            return (NULL);
        }
    }
}

// The read_and_append function reads from the file descriptor and appends the data to the static data.
// The extract_line function checks for a newline, extracts the line, and updates data.
// Finally, get_next_line orchestrates the process by calling these functions, returning lines until EOF is reached. It’s clean, modular, and efficient