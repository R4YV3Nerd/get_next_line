/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/25 11:38:03 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_and_append(int fd, char *data)
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

static char *extract_line(char **data)
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

char *get_next_line(int fd)
{
    static char *data[1024]; 
    char        *line;

    if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0) // Check FD limits, if fd > 1024 it will return NULL because we can't have more than 1024 file descriptors.
        return (NULL);
    while (1)
    {
        if (data[fd])
        {
            line = extract_line(&data[fd]);
            if (line)
                return (line);
        }
        data[fd] = read_and_append(fd, data[fd]);
        if (!data[fd])
            return (NULL);
        if (!*data[fd])
        {
            free(data[fd]);
            data[fd] = NULL;
            return (NULL);
        }
    }
}