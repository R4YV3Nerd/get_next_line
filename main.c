#include "get_next_line.h"
#include <stdio.h>

int main()
{
    char *line;
    int fd = open("test_file.txt", O_RDONLY); // read the line using the read function
    line = get_next_line(fd); // we assign the return value to a value so we can return it
    printf("%s", line); // we simply print the line
    free(line); // WE FREE THE LINE!
    if (fd == -1)
    {
        perror("Error opening file"); // error handling
        return 1;
    }
    int i = 0; // we set i to 0 so we can iterate through the lines using it
    while ((line = get_next_line(fd)) != NULL && i < 1) // while the function is returning a non null 
                                                        // value and i is less then the max that we are willing to read
                                                        // we continue to iterate and print the lines.
    {
        printf("%s", line); // we print...
        free(line);
        i++; // we iterate.
    }
    if(i == 1)
        free(line); // we free the line left after the iteration.
    close(fd); // finally we close the fd.
    return 0;
}
