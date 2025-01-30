/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/31 00:50:13 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef FDS_MAX
# define FDS_MAX 1024
# endif

static int  read_and_clean(int fd, char *line, char **next_line) // two asterisks because we want to access and modify the value of a variable that is outside the function
{
    int ret;

    ret = read(fd, line, BUFFER_SIZE);
    if (ret < 0) // if read fails we return -1
    {
        free(*next_line);
        return (-1);
    }
    while (ret > 0) // if read was successful we read the file until we reach the end of the file or a newline character is found
    {
        *next_line = ft_strjoin(*next_line, line); // here we join the read line to the next_line which is the line that will be returned
        if (ft_clean(line) > 0) // if a newline is found we return the next_line and stop reading the file and cleaning the line
            break ;
        ret = read(fd, line, BUFFER_SIZE);
    }
    return (ret);
}

char    *get_next_line(int fd) // each time we call this function we read the file and return a line until we reach the end of the file and if we reach a new line character we return the line and stop reading the file
{
    static char     line[FDS_MAX][BUFFER_SIZE + 1]; // we add 1 to the buffer size to store the '\0' character so we dont have to add it later
    char            *next_line;

    if (fd < 0 || fd >= FDS_MAX || BUFFER_SIZE < 1) // we check if the file descriptor is valid and if the buffer size is valid
        return (NULL);
    next_line = ft_strjoin(0, line[fd]); // during the first call, line is empty so we pass 0 to ft_strjoin to only allocate memory for line[fd] and avoid memory leaks
    if (ft_clean(line[fd]) > 0) // we check if a newline character was found in the current line
        return (next_line);
    if (read_and_clean(fd, line[fd], &next_line) < 0) // reads the file and cleans by calling the ft_clean function
        return (NULL);
    return (next_line);
}