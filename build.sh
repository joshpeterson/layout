#!/bin/sh
mkdir -p foo
cd build
set -e
ninja
./layout_test
