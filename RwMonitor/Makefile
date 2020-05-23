# Internal makefile for Ransomware monitor, use for testing..

LINK_TARGET = RwMonitorUnitTests
OBJS = RwMonitorUnitTests.o RwMonitor.o FsAction.o Heuristics.o 
REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	echo All done

$(LINK_TARGET) : $(OBJS)
	g++ -std=c++0x -g -o $@ $^

%.o : %.cpp
	g++ -std=c++0x -g -o $@ -c $<

FsAction.o: FsAction.cpp
Heuristics.o: Heuristics.cpp
RwMonitor.o: RwMonitor.cpp
RwMonitorUnitTests.o: RwMonitorUnitTests.cpp

clean:
	rm -f $(REBUILDABLES)
	echo Clean done