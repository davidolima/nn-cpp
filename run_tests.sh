#!/usr/bin/env sh

echo [!] Compiling testing API...
g++ -Wall -Wextra -Wpedantic -o test src/test.cpp
./test
