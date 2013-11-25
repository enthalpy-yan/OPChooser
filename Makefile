CC=g++
SOURCEDIR=./source
CFLAGS=-c -Wall 
LDFLAGS=`/usr/bin/curl-config --cflags` `/usr/bin/curl-config --libs` -ljsoncpp
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=finalProject

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:  
	rm -rf $(SOURCEDIR)/*.o
	rm finalProject

