#!/bin/bash
#add all modules

cd '#vision'
./build.sh
cd '../#communication'
./build.sh
cd '../'

qmake -o Makefile simulator.pro
make
