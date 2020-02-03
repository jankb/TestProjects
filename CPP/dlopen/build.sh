#!/bin/bash

g++ -fPIC -c math.cpp

g++ -shared -o libmathtest.so.1.0 math.o

g++ -ldl main.cpp


