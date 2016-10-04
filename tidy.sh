#!/bin/sh
if [ $# -eq 0 ] ; then
  #FILES="src/*.cpp test/*.cpp"
  FILES=`git diff  --name-only --diff-filter=AMR '*.cpp' | xargs`
else
  FILES="$1"
fi
echo Checking $FILES
clang-tidy $FILES -config='' -- -std=c++14 -I/usr/lib/llvm-3.8/include
