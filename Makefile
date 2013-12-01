CC=g++
INCLUDE=-I./include
SOURCEDIR=./source
CFLAGS=-c -Wall  
LDFLAGS=-lcurl -ljsoncpp -lboost_program_options-mt -lboost_date_time-mt
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=finalProject

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INCLUDE) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ 

clean:  
	rm -rf $(SOURCEDIR)/*.o
	rm $(EXECUTABLE)
	rm *.log

