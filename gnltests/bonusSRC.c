#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    int fd3 = open("test3.txt", O_RDONLY);
    int fd4 = open("test4.txt", O_RDONLY);

    char *line;
    if (fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0)
    {
        perror("Error opening file");
        return 1;
    }

    int i = 0;
    while(i < 4)
    {
    
    line = get_next_line(fd1);
    if (line != NULL)
    {
        printf("%s", line);
        free(line);
    }

    line = get_next_line(fd2);
    if (line != NULL)
    {
        printf("%s", line);
        free(line);
    }

    line = get_next_line(fd3);
    if (line != NULL)
    {
        printf("%s", line);
        free(line);
    }
    line = get_next_line(fd4);
    if (line != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    i++;
    
    }

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    return 0;
}
