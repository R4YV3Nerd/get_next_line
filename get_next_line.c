/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:23:12 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/03 23:49:10 by maitoumg         ###   ########.fr       */
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
        storage = ft_strdup("");z

    while (!ft_strchr(storage, '\n')) 
    // Keep reading until a newline ('\n') is found in the storage.
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE); 
        // Reads up to BUFFER_SIZE bytes from the file descriptor into the buffer.
        
        if (bytes_read <= 0) 
            break; 
        // If read returns 0 (EOF) or -1 (error), exit the loop.

        buffer[bytes_read] = '\0'; 
        // Null-terminate the buffer to treat it as a valid string.

        storage = ft_strjoin(storage, buffer); 
        // Append the buffer's content to storage. 
        // ft_strjoin handles memory allocation for the concatenated result.
    }

    line = extract_line_from_storage(&storage); 
    // Extract the line from storage, up to the first newline character. 
    // Updates storage to hold any leftover data after the extracted line.

    return (line); 
    // Returns the extracted line, or NULL if no more lines can be read.
}
