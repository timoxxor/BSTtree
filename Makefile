CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: out

out: main.cpp BSTree.cpp BSTree.hpp
	$(CXX) $(CXXFLAGS) -o out main.cpp BSTree.cpp

run: out
	./out

clean:
	rm -f out
