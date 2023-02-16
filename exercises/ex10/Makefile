# Cedric Nagata
# nagatac@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testcomplex

# default target
ex10: ex10.o Vector.o
	$(CXX) $(CPPFLAGS) -o ex10 ex10.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c Vector.cc

ex9.o: ex9.cc Vector.h
	$(CXX) $(CPPFLAGS) -c ex10.cc

# phony target - delete built files (including OS X debug files)
clean:
	rm -rf ex10 *.o *~ ex10.dSYM