###########################################################################
##                        Makefile for (Sorting)                         ##
###########################################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3

sorter: sorter.o sortAlgs.o
	${CXX} ${LDFLAGS} -o sorter sorter.o sortAlgs.o

sortAlgs.o:   sortAlgs.cpp	sortAlgs.h
sorter.o:     sorter.cpp	sortAlgs.h

clean:
	rm -rf sorter *.o *.dSYM