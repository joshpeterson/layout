#!/bin/sh
set -e
if [ ! -d build ]; then
  mkdir build
fi
cd build
if [ ! -d Debug ]; then
  mkdir Debug
fi
cd Debug
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake -DCMAKE_BUILD_TYPE=Debug ../.. -GNinja
ninja
./layout_test
cd ../..
