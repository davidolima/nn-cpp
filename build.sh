#!/usr/bin/env sh

g++ -Wall -Wextra -Wpedantic -o main.o main.cpp nn.cpp la.cpp operators.cpp -ggdb
g++ -Wall -Wextra -Wpedantic -o tests.o tests.cpp nn.cpp la.cpp operators.cpp
