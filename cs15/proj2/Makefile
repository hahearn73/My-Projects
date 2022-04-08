#test# Harry Ahearn cs15 SixDegrees Makefile
# Makefile for Six Degrees
#
# Project 2 (fall 2020)
#
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

SixDegrees: main.o SixDegrees.o CollabGraph.o Artist2.o
	${CXX} main.o SixDegrees.o CollabGraph.o Artist2.o -o SixDegrees

CollabGraph_test: CollabGraph_test.o CollabGraph.o Artist.o
	${CXX} CollabGraph_test.o CollabGraph.o Artist.o -o CollabGraph_test
	
%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf SixDegrees *.o *.dSYM
