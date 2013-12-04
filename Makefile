CC=g++
INCLUDE=-I./include -I./Shared
SOURCEDIR=./source
CFLAGS=-DIB_USE_STD_STRING -Wall -c
LDFLAGS=-lcurl -ljsoncpp -lboost_program_options-mt -lboost_date_time-mt
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=OPChooser

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INCLUDE) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ 

clean:  
	rm -rf $(SOURCEDIR)/*.o
	rm $(EXECUTABLE)
	rm *.log

