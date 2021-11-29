#!/bin/bash

g++ -c instrument.cpp
g++ -c instrumentMain.cpp
g++ -c percussiveInstrument.cpp
g++ -c pitchedInstrument.cpp
g++ -c snare.cpp
g++ -c violin.cpp


g++ -o instrument instrument.o instrumentMain.o percussiveInstrument.o pitchedInstrument.o snare.o violin.o
