#!/bin/sh
g++ -c main.cc -O3 -o main.o
g++ -c alg.cc -O3 -o alg.o
g++ alg.o main.o -O3 -o main
#./main;
