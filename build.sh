#!/usr/bin/env sh

echo [!] Compiling tests...
g++ -Wall -Wextra -Wpedantic -o test src/test.cpp
echo [!] Done!
