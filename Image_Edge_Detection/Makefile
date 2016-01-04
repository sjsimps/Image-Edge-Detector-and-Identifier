CPP_FLAGS = -O2 -Wall -std=c++11
SRC = main.cpp lodepng.cpp image.cpp object_detector.cpp

.PHONY: all
all: png_edge_detection

png_edge_detection: $(SRC)
	g++ $(CPP_FLAGS) $(SRC) -o $@
