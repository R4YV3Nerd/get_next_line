#include "get_next_line.h"  // Use quotes for local headers
#include <stdio.h>          // For printf
#include <fcntl.h>          // For open
#include <stdlib.h>         // For free
#include <unistd.h>         // For close

void test_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;

    if (fd == -1)
    {
        perror("Error opening file");  // Enclose string in quotes
        return;
    }

    printf("Testing file: %s\n", filename);  // Enclose string in quotes
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    printf("\nEnd of file: %s\n\n", filename);  // Enclose string in quotes
}

int main(void)
{
    // Test empty file
    test_file("test_empty.txt");  // Enclose string in quotes

    // Test file with one line (no newline at the end)
    test_file("test_one_line_no_nl.txt");

    // Test file with one line (newline at the end)
    test_file("test_one_line_with_nl.txt");

    // Test file with multiple lines
    test_file("test_multiple_lines.txt");

    // Test file with very long lines
    test_file("test_long_line.txt");

    // Test file with alternating empty and non-empty lines
    test_file("test_alternating_lines.txt");

    // Test file with only newlines
    test_file("test_only_newlines.txt");

    // Test file with large buffer size
    test_file("test_large_buffer.txt");

    return (0);
}
