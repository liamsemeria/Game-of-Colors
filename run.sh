#!/bin/bash

# before running do "chmod u+x run.sh"

# this worked for me on MacOS 12.4 Monterey, using SDL2 version 2.24.0

set -u -e # exit script at first error
clang++ main.cpp Game.cpp brush.cpp -std=c++11 -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -o sim
./sim
