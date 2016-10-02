#!/bin/sh
if [ $# -eq 0 ] ; then
  FILES="src/*.cpp test/*.cpp"
else
  FILES="$1"
fi
clang-tidy $FILES -config='' -- -std=c++14 -I/usr/lib/llvm-3.8/include
