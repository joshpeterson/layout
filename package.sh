#!/bin/bash
if [ -f layout.tar.gz ]; then
  rm layout.tar.gz
fi
if [ -d layout-package ]; then
  rm -rf layout-package/
fi

./release.sh

mkdir layout-package
cp build/Release/layout layout-package
cp /usr/lib/llvm-5.0/lib/libclang-5.0.so.1 layout-package
cp /usr/lib/llvm-5.0/lib/libLLVM-5.0.so.1 layout-package
cp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 layout-package
cp /lib/x86_64-linux-gnu/libtinfo.so.5 layout-package

declare -a rdirectories=("/usr/include/c++/7.2.0"
                         "/usr/include/c++/7.2.0/backward"
                         "/usr/include/x86_64-linux-gnu")
for i in "${rdirectories[@]}"
do
  cp -r --parents $i/* layout-package
done

declare -a directories=("/usr/include"
                        "/usr/lib/llvm-5.0/lib/clang/5.0.0/include")
for j in "${directories[@]}"
do
  # Don't print messages about omitting a directory
  cp --parents $j/* layout-package 2>&1 | grep -v "omitting directory"
done

tar -czf layout.tar.gz layout-package/
if [ -d layout-package ]; then
  rm -rf layout-package/
fi
