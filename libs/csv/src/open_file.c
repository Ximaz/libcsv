#include <csv_parser.h>

int open_file(char const *filename)
{
    int fd = -1;
    struct stat sbuf;
    int stat_exit = stat(filename, &sbuf);

    if (stat_exit != 0)
        return -1;
    if (!S_ISREG(sbuf.st_mode))
        return -1;
    fd = open(filename, O_RDONLY);
    if (fd < 3)
        return -1;
    return fd;
}