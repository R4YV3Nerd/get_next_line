#include "get_next_line.h"
#include <stdio.h>

int main()
{
	int fd1 = open("testtttt.txt", O_RDONLY);
	int fd2 = open("test_empty.txt", O_RDONLY);
	int fd3 = open("test_long_line.txt", O_RDONLY);

	char *line = get_next_line(fd1);

    while (line)
    {
        printf("FD 1: %s", line);
        free(line);
        line = get_next_line(fd1);
    }

    line = get_next_line(fd2);

    while (line)
    {
        printf("FD 2: %s", line);
        free(line);
        line = get_next_line(fd2);
    }

    line = get_next_line(fd3);

    while (line)
	{
        printf("FD 3: %s", line);
        free(line);
        line = get_next_line(fd3);
    }

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}



// int main()
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);
//     int fd3 = open("file3.txt", O_RDONLY);

//     int fds[] = {fd1, fd2, fd3};
//     char *line;
//     int i = 0;

//     while (i < 3)
//     {
//         line = get_next_line(fds[i]);
//         while (line)
//         {
//             printf("FD %d: %s", i + 1, line);
//             free(line);
//             line = get_next_line(fds[i]);
//         }
//         i++;
//     }

//     close(fd1);
//     close(fd2);
//     close(fd3);

//     return 0;
// }