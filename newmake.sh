#!/bin/bash

export PROJ_HOME=$PWD
rm -rf build
mkdir build
cd build
cmake ..
make
cd ProjectButton
explorer.exe .
