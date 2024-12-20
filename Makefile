PROJECT = editBMP

CXX = g++

CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

DEPS=$(wildcard *.h)



.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROJECT): main.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(PROJECT)
