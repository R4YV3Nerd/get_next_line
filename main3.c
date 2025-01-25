#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("testtttt.txt", O_RDONLY);
    char *line;

    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    int i = 0;
    while((line= get_next_line(fd))!= NULL && i < 2)
    {
        printf("%s", line);
        free(line);
        i++;
    }
    if (i == 2)
        free(line);
    close(fd);
}