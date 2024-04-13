#!/usr/bin/env sh

g++ -Wall -Wextra -Wpedantic -o main main.cpp nn.cpp la.cpp operators.cpp -ggdb
g++ -Wall -Wextra -Wpedantic -o tests tests.cpp nn.cpp la.cpp operators.cpp
