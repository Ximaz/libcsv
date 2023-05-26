#include <csv_parser.h>

size_t get_lines_number(int fd)
{
    int c = 0;
    ssize_t read_byte = 0;
    size_t lines = 0;

    do {
        read_byte = read(fd, &c, sizeof(char));
        if (read_byte <= 0)
            break;
        if (c == '\n')
            ++lines;
    } while (c);
    lseek(fd, 0, SEEK_SET);
    return lines;
}
