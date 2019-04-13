CC=g++
RM=rm -f
CFLAGS=-W -Wall -pedantic -std=c++11
LIBINCLUDES=../../libs/catch/catch.hpp

SOURCES=$(wildcard src/*.cpp)
COBJECTS=$(SOURCES:src/%.cpp=bin/obj/%.o)
LIBOBJECTS=bin/obj/pugixml.o

OBJECTS=$(COBJECTS) $(LIBOBJECTS)

EXEC=tests
TARGETLIBS=core

all: makebuild $(EXEC) $(TARGETLIBS)

# Create build structure
makebuild: 
	mkdir bin/;mkdir bin/obj/

# Core shared library
core: $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/core.a $^ 

# Tests executable
tests: $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/tests $^

# Construct object files
bin/obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Build PugiXML library
bin/obj/pugixml.o:libs/pugixml/pugixml.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f bin/obj/*.o bin/$(EXEC) bin/core.a
