CXX   = mpic++

EXE = porto
CXXFLAGS = -Wno-deprecated-register -O0 -std=c++17 -g -Wall

SRC = ./src
OBJ = ./obj

SOURCES := $(wildcard src/*)
OBJECTS := ${SOURCES:%=$(OBJ)/%.o}

.PHONY: all

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

$(OBJ)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I./include -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj/*
	rm -f $(EXE)