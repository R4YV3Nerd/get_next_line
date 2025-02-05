#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char *ft_strjoin(char *s1, char *s2) 
{
	char *res;
	int i;
	int j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

char *ft_read_buffer_size(int fd, char *backup)
{
	char *buffer;
	int len;

	buffer = (char *)malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_strchr(backup, '\n') == NULL)
	{
		len = read(fd, buffer ,BUFFER_SIZE);
		if (len < 0)
		{
			free(buffer);
			free (backup);
			backup = NULL;
			return (NULL);
		}
		if (len == 0)
			break;
		buffer[len] = '\0';
		backup = ft_strjoin(backup, buffer);
		if (!backup)
			return (NULL);
	}
	free (buffer);
	return (backup);
}

char	*ft_get_line(char  **backup)
{
	char 	*line;
	char 	*next_line;
	int		i;
	int		j;

	if (!*backup || !(*backup)[0])
		return (free(*backup), *backup = NULL, NULL);
	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (free(*backup), *backup = NULL, NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*backup)[j];
		j++;
	}
	line[j] = '\0';
	next_line = ft_strdup(&(*backup)[i]);
	return (free(*backup),*backup = next_line, line);
}

char *get_next_line(int fd)
{
	static char *backup;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	backup = ft_read_buffer_size(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_get_line(&backup);
	if (!line)
	{
		free(backup);
		backup = NULL;
	}
	if (backup && !backup[0])
	{
		free(backup);
		backup = NULL;
	}
	return (line);
}
