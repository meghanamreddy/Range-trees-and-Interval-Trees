CC = g++
CXX = $(CC)
DEBUG = -g -Wno-deprecated -fPIC

TARGETS = windowing
C_SRCS = interval_tree.cpp binaryRangeTree.cpp main.cpp

CXXFLAGS = $(CFLAGS)

all: ${TARGETS}


windowing: interval_tree.cpp binaryRangeTree.cpp main.cpp
	g++ interval_tree.cpp binaryRangeTree.cpp main.cpp -o windowing -std=c++11

clean:
	rm windowing



