#include <csv_parser.h>

void destroy_csv_data(csv_data_t *self)
{
    size_t i = 0;

    if (!self)
        return;
    if (self->header)
        free_cols(self->header, self->columns_number);
    if (self->body && self->rows_number > 0) {
        while (i < self->rows_number)
            free_cols(self->body[i++], self->columns_number);
        free(self->body);
    }
    free(self);
}