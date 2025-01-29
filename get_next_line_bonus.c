/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/29 07:51:37 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef FDS_MAX
# define FDS_MAX 1024
# endif

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
    static char     line[FDS_MAX][BUFFER_SIZE + 1];
    char            *next_line;

    if (fd < 0 || fd >= FDS_MAX || BUFFER_SIZE < 1)
        return (NULL);
    next_line = ft_strjoin(0, line[fd]);
    if (ft_clean(line[fd]) > 0)
        return (next_line);
    if (read_and_clean(fd, line[fd], &next_line) < 0)
        return (NULL);
    return (next_line);
}