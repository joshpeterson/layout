#!/bin/sh
if [ $# -eq 0 ] ; then
  FILES=`git diff  --name-only --diff-filter=AMR '*.cpp' | xargs`
  if [ -z "$FILES"]; then
    FILES="src/*.cpp test/*.cpp"
  fi
else
  FILES="$1"
fi
echo Checking $FILES
clang-tidy $FILES -config='' -- -std=c++14 -I/usr/lib/llvm-3.8/include
