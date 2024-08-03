#!/bin/bash

INSTALL_DIR="/usr/local/lib"

if ! [ -d "./build" ]; then
  echo "No build directory found. Build the library in first place using the GNU Make tool."
  exit 1
fi

if ! [ -f "./build/libjcon.so.1.0.0" ]; then
  echo "No shared library object found in the build directory. Make sure you executed the make instruction."
fi

cp ./build/libjcon.so.1.0.0 $INSTALL_DIR
ln -s /usr/local/lib/libjcon.so.1.0.0 /usr/local/lib/libjcon.so
ldconfig
echo "Successfully installed the library."
