#!/bin/sh
set -e
echo Building in debug
./debug.sh
make clean
echo Building in release
./release.sh
