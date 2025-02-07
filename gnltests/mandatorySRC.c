#include "get_next_line.h"
#include <stdio.h>

int main()
{
	int fd = open("test1.txt", O_RDONLY);
	char *line;

	if (fd < 0)
	{
		perror("Error opening file");
		return 1;
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}