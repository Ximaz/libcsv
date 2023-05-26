# CSV Parser
This repository was created in order to create a ``libcsv.a`` using the C language. Because I wanted to challenge myself doing a parser, and having to start somewhere, I decided to try to make one for CSV.

# Installation
```bash
# ===============================
# |    Clone the repository     |
# ===============================
git clone https://github.com/Ximaz/libcsv.git
cd libcsv

make -sC libs # Builds the libcsv.a

# ===============================
# | Once you changed src/main.c |
# ===============================
make csv_parser # Build the csv_parser program

# Example :
# ./csv_parser <my_csv_file.csv>
#
```
