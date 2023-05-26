#pragma once

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef char ** column_t;

typedef struct s_csv_data {
    column_t header;
    column_t *body;
    size_t columns_number;
    size_t rows_number;
} csv_data_t;

char *read_line(int fd);
size_t get_lines_number(int fd);
int open_file(char const *filename);
column_t parse_line(char *line, char delimiter);
void free_cols(char **cols, size_t cols_number);

#define ON_QUOTE_ESCAPING(line, index, handler)         \
    if (line[index] == '"' && line[index + 1] == '"') { \
        index += 2;                                     \
        handler;                                        \
        continue;                                       \
    }

#define ON_STRING_END(line, index, read_string, handler) \
    if (line[index] == '"' && line[index + 1] != '"') {  \
        read_string = !read_string;                      \
        handler;                                         \
        continue;                                        \
    }

#define ON_NEW_COLUMN(line, index, delimiter, read_string, handler) \
    if (line[index] == delimiter && !read_string)                   \
        handler;


csv_data_t *parse_from_file(char const *filename, char delimiter);
void destroy_csv_data(csv_data_t *self);
