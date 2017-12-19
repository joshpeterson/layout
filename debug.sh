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
cmake -DCMAKE_BUILD_TYPE=Debug ../.. -GNinja
ninja
./layout_test
cd ../..
ln -sf build/Debug/compile_commands.json compile_commands.json
