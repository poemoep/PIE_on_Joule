#!/bin/sh
cd src
g++ -c *.cpp -O2
g++ -o zigsowApp *.o -O2 `pkg-config opencv --cflags --libs`
mv zigsowApp ../
