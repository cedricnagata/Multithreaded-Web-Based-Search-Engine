# Cedric Nagata
# nagatac@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testcomplex

# default target
ex16: ex16.o Network.o
	$(CXX) $(CPPFLAGS) -o ex16 ex16.o Network.o

# individual source files
Network.o: Network.cc Network.h
	$(CXX) $(CPPFLAGS) -c Network.cc

ex16.o: ex16.cc Network.h
	$(CXX) $(CPPFLAGS) -c ex16.cc

# phony target - delete built files (including OS X debug files)
clean:
	rm -rf ex16 *.o *~ ex16.dSYM