#!/bin/bash

# Create an empty file
> test_empty.txt

# Create a file with one line (no newline at the end)
echo -n "This is a single line without a newline" > test_one_line_no_nl.txt

# Create a file with one line (newline at the end)
echo "This is a single line with a newline" > test_one_line_with_nl.txt

# Create a file with multiple lines
echo -e "Line 1\nLine 2\nLine 3" > test_multiple_lines.txt

# Create a file with a very long line
echo "This is a very long line with no newline until the end" > test_long_line.txt

# Create a file with alternating empty and non-empty lines
echo -e "Line 1\n\nLine 2\n\nLine 3" > test_alternating_lines.txt

# Create a file with only newlines
echo -e "\n\n\n\n\n" > test_only_newlines.txt

# Create a file with a large buffer size (e.g., 10,000 characters)
python3 -c 'print("A" * 10000)' > test_large_buffer.txt

echo "Test files generated successfully!"
