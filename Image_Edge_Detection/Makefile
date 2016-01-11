CPP_FLAGS = -O2 -Wall -std=c++11
DEBUG_FLAGS += -g
PROG = png_edge_detection
SRC = main.cpp lodepng.cpp image.cpp object_detector.cpp

.PHONY: all
all: png_edge_detection

.PHONY: debug
debug: 
	g++ $(CPP_FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(PROG)

.PHONY: clean
clean:
	rm png_edge_detection

png_edge_detection: $(SRC)
	g++ $(CPP_FLAGS) $(SRC) -o $(PROG)
