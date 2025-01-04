#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void ft_strcpy(char *dest, const char *src, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
}

char *ft_strjoin(char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    char *joined;
    size_t i;
    size_t j;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);

    joined = malloc(len1 + len2 + 1);
    if (!joined)
        return (NULL);

    ft_strcpy(joined, s1, len1);

    i = len1;
    j = 0;
    while (j < len2)
    {
        joined[i + j] = s2[j];
        j++;
    }

    joined[len1 + len2] = '\0';
    return (joined);
}

char *extract_line_and_update_storage(char **storage)
{
    size_t i;
    size_t j;
    char *line;
    char *new_storage;

    i = 0;
    while ((*storage)[i] && (*storage)[i] != '\n')
        i++;
    if ((*storage)[i] == '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    j = 0;
    while (j < i)
        line[j] = (*storage)[j], j++;
    line[i] = '\0';
    new_storage = ft_strdup(*storage + i);
    free(*storage);
    *storage = new_storage;
    return (line);
}

