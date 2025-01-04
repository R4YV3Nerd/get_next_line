/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:23:12 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/04 06:15:09 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

char *get_next_line(int fd) 
{
    static char *storage = NULL; 
    char buffer[BUFFER_SIZE + 1];
	char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0) 
        return (NULL);

    if (!storage)
        storage = ft_strdup("");

    while (!ft_strchr(storage, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) 
            break;
        buffer[bytes_read] = '\0';
        storage = ft_strjoin(storage, buffer);
    }
    line = extract_line_from_storage(&storage);
    return (line);
}
