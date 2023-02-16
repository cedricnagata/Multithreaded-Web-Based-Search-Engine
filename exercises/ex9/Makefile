# Cedric Nagata
# nagatac@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testcomplex

# default target
ex9: ex9.o Vector.o
	$(CXX) $(CPPFLAGS) -o ex9 ex9.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c Vector.cc

ex9.o: ex9.cc Vector.h
	$(CXX) $(CPPFLAGS) -c ex9.cc

# phony target - delete built files (including OS X debug files)
clean:
	rm -rf ex9 *.o *~ ex9.dSYM