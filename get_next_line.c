/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/29 07:49:45 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int  read_and_clean(int fd, char *line, char **next_line)
{
    int i;

    i = read(fd, line, BUFFER_SIZE);
    if (i < 0)
    {
        free(*next_line);
        return (-1);
    }
    while (i > 0)
    {
        *next_line = ft_strjoin(*next_line, line);
        if (ft_clean(line) > 0)
            break ;
        i = read(fd, line, BUFFER_SIZE);
    }
    return (i);
}

char    *get_next_line(int fd)
{
    static char     line[BUFFER_SIZE + 1];
    char            *next_line;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    next_line = ft_strjoin(0, line);
    if (ft_clean(line) > 0)
        return (next_line);
    if (read_and_clean(fd, line, &next_line) < 0)
        return (NULL);
    return (next_line);
}