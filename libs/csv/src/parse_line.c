#include <csv_parser.h>

static size_t next_token_length(char *line, char delimiter, size_t index)
{
    size_t length = 0;
    int read_string = 0;

    while (line[index]) {
        ON_QUOTE_ESCAPING(line, index, ++length)
        ON_STRING_END(line, index, read_string, ++index)
        ON_NEW_COLUMN(line, index, delimiter, read_string, break)
        ++length;
        ++index;
    }
    return ++length;
}

static size_t find_cols_number(char *line, char delimiter, size_t index)
{
    size_t cols = 0;
    int read_string = 0;

    while (line[index]) {
        ON_QUOTE_ESCAPING(line, index, ;)
        ON_STRING_END(line, index, read_string, ++index)
        ON_NEW_COLUMN(line, index, delimiter, read_string, ++cols)
        ++index;
    }
    if (line[index] == 0)
        ++cols;
    return cols;
}

static char *parse_next_token(char *line, char delimiter, size_t *index)
{
    char *token = 0;
    size_t cursor = 0;
    int read_string = 0;
    size_t length = next_token_length(line, delimiter, *index);

    if (length == 0)
        return 0;
    token = (char *) malloc(sizeof(char) * (length + 1));
    if (!token)
        return 0;
    while (line[(*index)]) {
        ON_QUOTE_ESCAPING(line, (*index), token[cursor++] = '"')
        ON_STRING_END(line, (*index), read_string, ++(*index))
        ON_NEW_COLUMN(line, (*index), delimiter, read_string, break)
        token[cursor++] = line[(*index)++];
    }
    token[cursor] = 0;
    ++(*index);
    return token;
}

column_t parse_line(char *line, char delimiter)
{
    size_t index = 0;
    size_t col_number = 0;
    size_t cols_number = find_cols_number(line, delimiter, index);
    column_t cols = 0;

    if (cols_number == 0)
        return 0;
    cols = (column_t) malloc(sizeof(char *) * (cols_number + 1));
    if (!cols)
        return 0;
    for (; col_number < cols_number; ++col_number) {
        cols[col_number] = parse_next_token(line, delimiter, &index);
        if (!cols[col_number]) {
            free_cols(cols, col_number);
            return 0;
        }
    }
    cols[cols_number] = 0;
    return cols;
}