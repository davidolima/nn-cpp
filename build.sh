#!/usr/bin/env sh

echo [!] Compiling main...
g++ -ggdb -Wall -Wextra -Wpedantic -o main main.cpp nn.cpp la.cpp operators.cpp
echo [!] Compiling tests...
g++ -Wall -Wextra -Wpedantic -o test test.cpp -ggdb
echo [!] Done!
