#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("testtttt.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("%s", line);
    free(line);
    return (0);

}
