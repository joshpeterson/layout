#!/bin/sh
if [ -f layout.tar.gz ]; then
  rm layout.tar.gz
fi
if [ -d cde-package ]; then
  rm -rf cde-package/
fi
./release.sh
cde ./layout
tar -czvf layout.tar.gz cde-package/ layout
if [ -d cde-package ]; then
  rm -rf cde-package/
fi
if [ -f cde.options ]; then
  rm cde.options
fi
