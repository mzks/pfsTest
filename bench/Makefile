TARGET = main

SRCS = $(TARGET).C
OBJS = $(TARGET).o

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS = $(ROOTCFLAGS) -Wall -fPIC
CXXLIBS = $(ROOTLIBS)
CC = g++

$(TARGET): $(OBJS)
	$(CC) $(CXXLIBS) $(OBJS) -o $@

.C.o:
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)
	rm -rf *.root
