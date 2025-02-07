#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef BONUS
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;

void assert_test(const char *test_name, int condition) {
    test_count++;
    if (condition) {
        printf(GREEN "[PASS]" RESET " %s\n", test_name);
        pass_count++;
    } else {
        printf(RED "[FAIL]" RESET " %s\n", test_name);
    }
}

int create_temp_file(const char *content) {
    char filename[] = "/tmp/gnl_test_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1)
        return -1;
    unlink(filename);
    write(fd, content, strlen(content));
    lseek(fd, 0, SEEK_SET);
    return fd;
}

/* Test Cases */
void test_empty_file(void) {
    int fd = create_temp_file("");
    char *line = get_next_line(fd);
    assert_test("Empty file", line == NULL);
    close(fd);
}

void test_single_line_no_nl(void) {
    int fd = create_temp_file("test");
    char *line = get_next_line(fd);
    assert_test("Single line no newline (content)", line && strcmp(line, "test") == 0);
    free(line);
    line = get_next_line(fd);
    assert_test("Single line no newline (EOF)", line == NULL);
    close(fd);
}

void test_single_line_with_nl(void) {
    int fd = create_temp_file("test\n");
    char *line = get_next_line(fd);
    assert_test("Single line with newline (content)", line && strcmp(line, "test\n") == 0);
    free(line);
    line = get_next_line(fd);
    assert_test("Single line with newline (EOF)", line == NULL);
    close(fd);
}

void test_multiple_lines(void) {
    int fd = create_temp_file("line1\nline2\nline3");
    char *line;
    
    line = get_next_line(fd);
    assert_test("Multiple lines (1)", line && strcmp(line, "line1\n") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Multiple lines (2)", line && strcmp(line, "line2\n") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Multiple lines (3)", line && strcmp(line, "line3") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Multiple lines (EOF)", line == NULL);
    close(fd);
}

void test_consecutive_newlines(void) {
    int fd = create_temp_file("\n\n\n");
    char *line;
    
    line = get_next_line(fd);
    assert_test("Consecutive newlines (1)", line && strcmp(line, "\n") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Consecutive newlines (2)", line && strcmp(line, "\n") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Consecutive newlines (3)", line && strcmp(line, "\n") == 0);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Consecutive newlines (EOF)", line == NULL);
    close(fd);
}

void test_invalid_fd(void) {
    char *line = get_next_line(-1);
    assert_test("Invalid file descriptor", line == NULL);
}

void test_large_buffer(void) {
    char long_line[1025];
    memset(long_line, 'a', 1024);
    long_line[1024] = '\0';
    strcat(long_line, "\n");
    
    int fd = create_temp_file(long_line);
    char *line = get_next_line(fd);
    assert_test("Large buffer (content)", line && strlen(line) == 1025);
    free(line);
    
    line = get_next_line(fd);
    assert_test("Large buffer (EOF)", line == NULL);
    close(fd);
}

#ifdef BONUS
void test_multiple_fds(void) {
    int fd1 = create_temp_file("file1 line1\nfile1 line2");
    int fd2 = create_temp_file("file2 line1\nfile2 line2");
    char *line1, *line2;

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    assert_test("Multiple FDs (1a)", line1 && strcmp(line1, "file1 line1\n") == 0);
    assert_test("Multiple FDs (1b)", line2 && strcmp(line2, "file2 line1\n") == 0);
    free(line1);
    free(line2);

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    assert_test("Multiple FDs (2a)", line1 && strcmp(line1, "file1 line2") == 0);
    assert_test("Multiple FDs (2b)", line2 && strcmp(line2, "file2 line2") == 0);
    free(line1);
    free(line2);

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    assert_test("Multiple FDs (EOF1)", line1 == NULL);
    assert_test("Multiple FDs (EOF2)", line2 == NULL);
    close(fd1);
    close(fd2);
}
#endif

int main(void) {
    printf("Running get_next_line tests...\n\n");

    test_empty_file();
    test_single_line_no_nl();
    test_single_line_with_nl();
    test_multiple_lines();
    test_consecutive_newlines();
    test_invalid_fd();
    test_large_buffer();

#ifdef BONUS
    test_multiple_fds();
#endif

    printf("\nResults: %d/%d tests passed\n", pass_count, test_count);
    return (pass_count == test_count) ? EXIT_SUCCESS : EXIT_FAILURE;
}

