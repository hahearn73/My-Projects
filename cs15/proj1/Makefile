###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Harry Ahearn 10/26/21

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) main.o RPNCalc.o DatumStack.o Datum.o parser.o -o CalcYouLater

main.o: main.cpp RPNCalc.h DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c main.cpp

RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

DatumStack_test: DatumStack_test.o DatumStack.o Datum.o
	$(CXX) DatumStack_test.o DatumStack.o Datum.o -o DatumStack_test

DatumStack_test.o: DatumStack_test.cpp
	$(CXX) $(CXXFLAGS) -c DatumStack_test.cpp

DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp
 
##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^