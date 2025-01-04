#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int i = 1;

    // Check if files are passed as arguments
    if (argc < 2)
    {
        printf("Please provide a file to test.\n");
        return (1);
    }

    // Process each file passed as command-line argument using a while loop
    while (i < argc)
    {
        // Open the file for reading
        fd = open(argv[i], O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening file");
            i++;  // Move to the next file if error opening the current one
            continue;
        }

        // Print which file is being tested
        printf("\nTesting file: %s\n", argv[i]);

        // Read lines one by one using get_next_line
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("Line: %s", line);  // Print the line
            free(line);  // Free the memory allocated by get_next_line
        }

        // Close the file after reading all lines
        close(fd);

        i++;  // Move to the next file
    }

    return (0);
}

