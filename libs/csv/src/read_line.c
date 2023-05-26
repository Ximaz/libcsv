#include <csv.h>

static char *read_n_bytes(int fd, size_t length)
{
    char *buffer = 0;
    ssize_t read_byte = 0;
    off_t offset_result = lseek(fd, -1 * length, SEEK_CUR);

    if (offset_result == -1)
        return 0;
    /* No + 1 because \n will become \0 */
    buffer = (char *) malloc(sizeof(char) * (length));
    if (!buffer)
        return 0;
    read_byte = read(fd, buffer, sizeof(char) * (length));
    if (read_byte == -1) {
        free(buffer);
        return 0;
    }
    buffer[length - 1] = 0;
    return buffer;
}

char *read_line(int fd)
{
    int c = 0;
    char *buffer = 0;
    size_t length = 0;
    ssize_t read_byte = 0;

    do {
        read_byte = read(fd, &c, sizeof(char));
        ++length;
    } while (read_byte > 0 && c != '\n');
    if (read_byte == -1 || read_byte == 0 || length == 1)
        return 0;
    buffer = read_n_bytes(fd, length);
    return buffer;
}