#!/bin/sh
set -e
if [ ! -d build ]; then
  mkdir build
fi
cd build
if [ ! -d Release ]; then
  mkdir Release
fi
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../.. -GNinja
ninja
./layout_test
