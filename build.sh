#!/bin/sh
set -e
echo Building in debug
./debug.sh
echo Building in release
./release.sh
