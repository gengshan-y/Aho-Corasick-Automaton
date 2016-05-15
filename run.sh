#!/bin/bash

## compile
make clean
make

## timing the search
echo "running 1000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_1000.txt 0
echo "running 5000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_5000.txt 0
echo "running 10000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_10000.txt 0
echo "running 50000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_50000.txt 0
echo "running 100000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_100000.txt 0
echo "running 500000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_500000.txt 0
echo "running 1000000 words"
./FindAllQueries ./input_files/dictionary.txt ./input_files/database_1000000.txt 0
