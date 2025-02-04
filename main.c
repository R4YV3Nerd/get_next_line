#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int fd = open("test1.txt", O_RDONLY);
    int fd1 = open("test2.txt", O_RDONLY);
    int fd2 = open("test3.txt", O_RDONLY);
    int fd3 = open("test4.txt", O_RDONLY);
    char *line;

    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    int i = 0;

    while (i < 3)
    {
       if (line) {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        }
        if (line) {
        line = get_next_line(fd1);
        printf("%s", line);
        free(line);
        }
        if (line) {
        line = get_next_line(fd2);
        printf("%s", line);
        free(line);
        }
        if (line) {
        line = get_next_line(fd3);
        printf("%s\n", line);
        free(line);
        }
        i++;

        i++;
    }

    close(fd);
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
