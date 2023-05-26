#include <stdio.h>
#include <csv_parser.h>

int main(int argc, char **argv)
{
    csv_data_t *csv = 0;

    if (argc != 2) {
        printf("Usage :\n\t%s <csv_file>\n", argv[0]);
        return 84;
    }
    csv = parse_from_file(argv[1], ',');
    if (!csv) {
        printf("An error occured while parsing the CSV file.\n");
        return 84;
    }

    /* ... Insert code to treat CSV ... */

    destroy_csv_data(csv);
    return 0;
}