#!/bin/bash

export PROJ_HOME=$PWD
cd build
make
cd ProjectButton
explorer.exe .