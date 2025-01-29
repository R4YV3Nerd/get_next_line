#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd1 = open("test_long_line.txt", O_RDONLY);
    int fd2 = open("testtttt.txt", O_RDONLY);
    int fd7 = open("binary.txt", O_RDONLY);
    
    char *line;
    int fd[3] = {fd1, fd2, fd7};

    int i = 0;
    while (i < 7 && fd[i] != -1 && fd[i] != 0)
    {
        while ((line = get_next_line(fd[i])) != NULL)
        {
            printf("%s", line);
            free(line);
        }
        close(fd[i]);
        i++;
    }
    return 0;
}
