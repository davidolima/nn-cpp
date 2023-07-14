#!/usr/bin/env sh

g++ -Wall -Wextra -Wpedantic -fsanitize=address -o main.o main.cpp la.cpp
