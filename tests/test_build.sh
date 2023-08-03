#!/usr/bin/env sh

g++ -Wall -Wextra -Wpedantic -std=c++17 -g $1 ../la.cpp ../strassen.cpp ../operators.cpp -o test.out
