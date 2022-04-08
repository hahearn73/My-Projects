#
# Makefile for lab 10
#
# lab10 (Spring 2021)
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++14
INCLUDES = $(shell echo *.h)

PathFinder: main.o PathFinder.o Graph.o City.o
		${CXX} -o $@ $^

%.o: %.cpp ${INCLUDES}
		${CXX} ${CXXFLAGS} -c $<

clean:
		rm -rf PathFinder *.o *.dSYM

provide:
	provide comp15 lab11 PathFinder.cpp PathFinder.h City.cpp City.h Graph.cpp Graph.h Makefile
