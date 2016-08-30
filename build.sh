#!/bin/sh
set -e
if [ -n "$COMPILER" ]
then
  make DEBUG=1 CXX=$COMPILER
else
  make DEBUG=1
fi
./layout_test
