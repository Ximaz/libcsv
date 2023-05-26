#include <csv.h>

static int init_csv_data(csv_data_t *self, int fd)
{
    size_t lines = get_lines_number(fd);

    self->header = 0;
    self->columns_number = 0;
    self->rows_number = --lines;
    if (self->rows_number <= 0)
        return -1;
    self->body = (column_t *) malloc(sizeof(column_t) * (self->rows_number));
    if (!self->body)
        return -1;
    return 0;
}

static int set_header(csv_data_t *self, int fd, char delimiter)
{
    size_t i = 0;
    char *header = read_line(fd);

    if (!header)
        return -1;
    self->header = parse_line(header, delimiter);
    free(header);
    if (!self->header)
        return -1;
    while (self->header[i++]);
    self->columns_number = --i;
    return 0;
}

static int set_body(csv_data_t *self, int fd, char delimiter)
{
    size_t i = 0;
    char *row = 0;
    column_t cols = 0;

    for (; i < self->rows_number; ++i) {
        row = read_line(fd);
        if (!row) {
            self->body[i] = 0;
            continue;
        }
        cols = parse_line(row, delimiter);
        free(row);
        self->body[i] = !cols ? 0 : cols;
    }
    return 0;
}

csv_data_t *csv_from_file(char const *filename, char delimiter)
{
    csv_data_t *self = 0;
    int fd = open_file(filename);

    if (fd < 3)
        return 0;
    self = (csv_data_t *) malloc(sizeof(csv_data_t));
    if (!self) {
        close(fd);
        return 0;
    }
    if (init_csv_data(self, fd) == -1) {
        free(self);
        close(fd);
        return 0;
    }
    if (set_header(self, fd, delimiter) == -1) {
        close(fd);
        destroy_csv_data(self);
        return 0;
    }
    if (set_body(self, fd, delimiter) == -1) {
        close(fd);
        destroy_csv_data(self);
        return 0;
    }
    close(fd);
    return self;
}