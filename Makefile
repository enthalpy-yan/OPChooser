CC=g++
INCLUDE=-I./include
SOURCEDIR=./source
CFLAGS=-c -Wall 
LDFLAGS=`/usr/bin/curl-config --cflags` `/usr/bin/curl-config --libs` -ljsoncpp
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=finalProject

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(INCLUDE) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ 

clean:  
	rm -rf $(SOURCEDIR)/*.o
	rm $(EXECUTABLE)

