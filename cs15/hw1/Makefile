#########################################################
#                   HOMEWORK 1: LISTS                   #
# by C.R. Calabrese, Jan-Feb 2021                       #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

default: unit_test

# this rule will run unit_test while compiling both
# CharArrayList and CharLinkedList
unit_test: unit_test_driver.o CharArrayList.o CharLinkedList.o
	$(CXX) unit_test_driver.o CharArrayList.o CharLinkedList.o
	
unit_test_driver.o: unit_tests.h CharArrayList.h \
                    CharLinkedList.h
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp 
	
CharArrayList.o: CharArrayList.cpp CharArrayList.h
	$(CXX) $(CXXFLAGS) -c CharArrayList.cpp
	
CharLinkedList.o: CharLinkedList.cpp CharLinkedList.h
	$(CXX) $(CXXFLAGS) -c CharLinkedList.cpp


# remove executables and object code from the current folder -- the 
# executable created by unit_test is called a.out
clean: 
	rm *.o a.out

# submit the homework
provide:
	provide comp15 hw1 \
	CharLinkedList.cpp CharLinkedList.h \
	CharArrayList.cpp  CharArrayList.h \
	unit_tests.h README Makefile