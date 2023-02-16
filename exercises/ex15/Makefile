# Cedric Nagata
# nagatac@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testcomplex

# default target
ex15: ex15.o Network.o
	$(CXX) $(CPPFLAGS) -o ex15 ex15.o Network.o

# individual source files
Network.o: Network.cc Network.h
	$(CXX) $(CPPFLAGS) -c Network.cc

ex15.o: ex15.cc Network.h
	$(CXX) $(CPPFLAGS) -c ex15.cc

# phony target - delete built files (including OS X debug files)
clean:
	rm -rf ex15 *.o *~ ex15.dSYM