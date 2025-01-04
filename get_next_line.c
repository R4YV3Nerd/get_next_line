#include "get_next_line.h"

static char *update_storage(char *storage, char *buffer)
{
    char *old_storage = storage;
    storage = ft_strjoin(storage, buffer);
    free(old_storage);
    return storage;
}

char *get_next_line(int fd)
{
    static char *storage;
    char buffer[BUFFER_SIZE + 1];
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!storage)
        storage = ft_strdup("");  // Initialize storage if NULL
    while (!ft_strchr(storage, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        storage = update_storage(storage, buffer);  // Use update_storage to handle memory
    }
    if (bytes_read <= 0 && !storage)
        return (NULL);
    line = extract_line_and_update_storage(&storage);
    return (line);
}

