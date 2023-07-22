#!/usr/bin/env sh

g++ -Wall -Wextra -Wpedantic -o main.o *.cpp
g++ -Wall -Wextra -Wpedantic -o tests.o tests/*.cpp nn.cpp la.cpp
