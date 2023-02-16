# Cedric Nagata
# nagatac@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testcomplex

# default target
ex13: ex13.o Cartesian.o Polar.o
	$(CXX) $(CPPFLAGS) -o ex13 ex13.o Cartesian.o Polar.o

# individual source files
Cartesian.o: Cartesian.cc Cartesian.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c Cartesian.cc

Polar.o: Polar.cc Polar.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c Polar.cc

ex13.o: ex13 Cartesian.h Polar.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c ex13.cc

# phony target - delete built files (including OS X debug files)
clean:
	rm -rf ex13 *.o *~ ex13.dSYM