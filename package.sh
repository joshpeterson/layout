#!/bin/bash
if [ -f layout.tar.gz ]; then
  rm layout.tar.gz
fi
if [ -d cde-package ]; then
  rm -rf cde-package/
fi
./release.sh
cde ./build/Release/layout

declare -a rdirectories=("/usr/include/c++/7.2.0"
                         "/usr/include/c++/7.2.0/backward"
                         "/usr/include/x86_64-linux-gnu")
for i in "${rdirectories[@]}"
do
  echo $i
  cp -r --parents $i/* cde-package/cde-root
done

declare -a directories=("/usr/include"
                        "/usr/lib/llvm-5.0/lib/clang/5.0.0/include")
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
