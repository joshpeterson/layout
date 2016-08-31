#!/bin/sh
set -e
if [ -n "$COMPILER" ]
then
  make DEBUG=0 CXX=$COMPILER
else
  make DEBUG=0
fi
./layout_test
