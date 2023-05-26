#!/bin/bash -e

function install {
    if [[ ! -d "libcsv" ]]; then
        git clone https://github.com/Ximaz/libcsv.git libcsv
    fi

    make -sC libcsv/libs
    sudo cp libcsv/libs/libcsv.a /usr/lib/libcsv.a
    sudo cp libcsv/libs/libcsv.a /usr/local/lib/libcsv.a
    sudo cp libcsv/include/csv.h /usr/include/csv.h
    sudo cp libcsv/include/csv.h /usr/local/include/csv.h
    make -sC libcsv/libs fclean
}

function uninstall {
    sudo rm -rf /usr/lib/libcsv.a
    sudo rm -rf /usr/local/lib/libcsv.a
    sudo rm -rf /usr/include/csv.h
    sudo rm -rf /usr/local/include/csv.h
}

if [[ "${1}" == "install" ]]; then
    install
elif [[ "${1}" == "uninstall" ]]; then
    uninstall
else
    echo "Unknowned parameter : ${1}"
    exit 1
fi
