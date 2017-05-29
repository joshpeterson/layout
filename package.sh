#!/bin/bash
if [ -f layout.tar.gz ]; then
  rm layout.tar.gz
fi
if [ -d cde-package ]; then
  rm -rf cde-package/
fi
./release.sh
cde ./layout

declare -a rdirectories=("/usr/include/c++/6"
                         "/usr/include/c++/6/backward"
                         "/usr/include/x86_64-linux-gnu")
for i in "${rdirectories[@]}"
do
  echo $i
  cp -r --parents $i/* cde-package/cde-root
done

declare -a directories=("/usr/include"
                        "/usr/lib/llvm-3.8/lib/clang/3.8.0/include")
for j in "${directories[@]}"
do
  cp --parents $j/* cde-package/cde-root
done

tar -czf layout.tar.gz cde-package/
if [ -d cde-package ]; then
  rm -rf cde-package/
fi
if [ -f cde.options ]; then
  rm cde.options
fi
