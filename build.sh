#!/bin/sh
mkdir -p build
cd build
cmake ..
make
./layout_test
