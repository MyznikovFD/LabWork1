PROJECT = editBMP
CXX = g++
CXXFLAGS = -Isrc -std=c++17 -Wall -fopenmp

SRC_DIR = src
IMAGES_DIR = images

DEPS = $(wildcard $(SRC_DIR)/*.h)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRCS))

.PHONY: default all clean

default: all

all: $(PROJECT)
	mkdir -p $(IMAGES_DIR)

%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROJECT): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm -f *.o
	rm -f $(PROJECT)
	find $(IMAGES_DIR) -type f ! -name 'source.bmp' -delete
