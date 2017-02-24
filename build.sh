#!/bin/sh
cd src
g++ -c *.cpp -O2
g++  *.o -O2 `pkg-config opencv --cflags --libs`
mv a.out ../
