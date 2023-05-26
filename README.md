# CSV Parser
This repository was created in order to create a ``libcsv.a`` using the C language. Because I wanted to challenge myself doing a parser, and having to start somewhere, I decided to try to make one for CSV.

# Install
```bash
curl -s -X GET https://raw.githubusercontent.com/Ximaz/libcsv/main/install.bash | /bin/bash
```

# Remove
```bash
curl -s -X GET https://raw.githubusercontent.com/Ximaz/libcsv/main/remove.bash | /bin/bash
```

# Documentation
The `csv.h` file contains two typedefs :

```c
typedef char ** column_t;

typedef struct s_csv_data {
    column_t header;        /* Holds CSV header (i.e. 'ID,Firstname,Name,Age') */
    column_t *body;         /* Holds all columns excepted the first one */
    size_t columns_number;  /* The number of columns present in one row */
    size_t rows_number;     /* The number of rows contained in 'body' */
} csv_data_t;
```

And also those two important functions :

```c
/* Reads the file from filename line by line and return the csv_data_t *. */
csv_data_t *csv_from_file(char const *filename, char delimiter);

/* Destroy the csv_data_t * in ordred not to have memleak. */
void destroy_csv_data(csv_data_t *self);
```

# Usage

### C Code Example

```c
/* main.c */
#include <csv.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    csv_data_t *csv = 0;

    if (argc != 2) {
        printf("Usage :\n\t%s <csv_file>\n", argv[0]);
        return 84;
    }
    csv = csv_from_file(argv[1], ',');
    if (!csv) {
        printf("An error occured while parsing the CSV file.\n");
        return 84;
    }

    /* ... Insert code to treat CSV ... */

    destroy_csv_data(csv);
    return 0;
}
```

### Compilation Example

```bash
gcc main.c -o csv_parser -lcsv
```

### Usage example

```bash
./csv_parser example.csv
```

# Knowned Issue
The parser won't work for CSV files whose lines are ending by `CRLF`. If you're on windows, you may reformat the file to transform `CRLF` into `LF`.
