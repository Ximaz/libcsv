#!/bin/bash -e

if [[ ! -d "libcsv" ]]; then
    git clone https://github.com/Ximaz/libcsv.git libcsv
fi

make -sC libcsv/libs
sudo cp libcsv/libs/libcsv.a /usr/lib/libcsv.a
sudo cp libcsv/libs/libcsv.a /usr/local/lib/libcsv.a
sudo cp libcsv/include/csv.h /usr/include/csv.h
sudo cp libcsv/include/csv.h /usr/local/include/csv.h
make -sC libcsv/libs fclean