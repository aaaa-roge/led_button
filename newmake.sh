#!/bin/bash

export PROJ_HOME=$PWD
rm -rf build
mkdir build
cd build
cmake ..
echo "if this worked run make at $PWD"