#include "get_next_line.h"
#include <stdio.h>


int main()
{
	int fd = open("tess.txt", O_RDONLY);
	int fd2 = open("tess.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	while ((line = get_next_line(fd2)) != NULL)
        {
                printf("%s", line);
                free(line);
        }
        close(fd);
	close(fd2);
	return (0);
}







// int main(void)
// {
//     int fd = open("test_file.txt", O_RDONLY);

//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }


//     char *line;
//     while ((line = get_next_line(fd)) != NULL) // always need to assign the return value to a variable to free it later o
//     {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }

// #include "get_next_line.h"
// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
//     int fd = open("test_file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }
