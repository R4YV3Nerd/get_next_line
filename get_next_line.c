#include "get_next_line.h"

static char *initialize_storage(char *storage)
{
    if (!storage)
        return ft_strdup("");
    return storage;
}

static int handle_read_error(int bytes_read, char **storage)
{
    if (bytes_read < 0 && *storage)
    {
        free(*storage);
        return 1;
    }
    if (bytes_read == 0 && (!*storage || !**storage))
        return 1;
    return 0;
}

static char *ft_strdup(const char *str)
{
    size_t len;
    char *copy;

    len = strlen(str) + 1;
    copy = malloc(len);
    if (copy)
        memcpy(copy, str, len);
    return copy;
}

static char *update_storage(char *storage, char *buffer)
{
    char *old_storage = storage;
    storage = ft_strjoin(storage, buffer);
    if (!storage)
    {
        free(old_storage);
        return NULL;
    }
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
        return NULL;

    storage = initialize_storage(storage);

    while (!ft_strchr(storage, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (handle_read_error(bytes_read, &storage))
            return NULL;

        buffer[bytes_read] = '\0';
        storage = update_storage(storage, buffer);
        if (!storage)
            return NULL;
    }

    line = extract_line_and_update_storage(&storage);
    if (!line)
    {
        free(storage);
        return NULL;
    }

    return line;
}

