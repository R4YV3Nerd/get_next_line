#include "get_next_line.h"

char *ft_strdup(const char *s)
{
    size_t len;
    size_t i;
    char *dup;

    len = 0;
    while (s[len])
        len++;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

char *ft_strjoin(char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    char *joined;

    len1 = 0;
    len2 = 0;
    while (s1[len1])
        len1++;
    while (s2[len2])
        len2++;
    joined = malloc(len1 + len2 + 1);
    if (!joined)
        return (NULL);
    i = 0;
    while (i < len1)
        joined[i] = s1[i], i++;
    j = 0;
    while (j < len2)
        joined[i + j] = s2[j], j++;
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
