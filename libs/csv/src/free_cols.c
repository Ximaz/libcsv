#include <csv_parser.h>

void free_cols(char **cols, size_t cols_number)
{
    size_t i = 0;

    if (!cols)
        return;
    if (cols_number > 0)
        for (; i < cols_number; ++i)
            free(cols[i]);
    else
        while (cols[i])
            free(cols[i++]);
    free(cols);
}