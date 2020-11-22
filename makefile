# the compiler: gcc for C program, define as g++ for C++
CC = g++

    # compiler flags:
    #  -g    adds debugging information to the executable file
    #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Weffc++ -std=c++11
TARGET = cTrace
TARGERDIR=bin/

all: clean Graph Session Agent Tree main target


Graph: cpp/Graph.cpp include/Graph.h
	$(CC) $(CFLAGS) -c cpp/Graph.cpp -o $(TARGERDIR)Graph.o

Session: include/Session.h cpp/Session.cpp
	$(CC) $(CFLAGS) -c cpp/Session.cpp -o $(TARGERDIR)Session.o

Agent: include/Agent.h cpp/Agent.cpp
	$(CC) $(CFLAGS) -c cpp/Agent.cpp -o $(TARGERDIR)Agent.o

Tree: include/Tree.h cpp/Tree.cpp
	$(CC) $(CFLAGS) -c cpp/Tree.cpp -o $(TARGERDIR)Tree.o

main: main.cpp
	$(CC) $(CFLAGS) -c -c main.cpp -o $(TARGERDIR)main.o

target : $(TARGERDIR)Agent.o $(TARGERDIR)Graph.o $(TARGERDIR)Session.o $(TARGERDIR)Tree.o $(TARGERDIR)main.o
	$(CC) $(CFLAGS) $(TARGERDIR)Agent.o $(TARGERDIR)Graph.o $(TARGERDIR)Session.o $(TARGERDIR)Tree.o $(TARGERDIR)main.o -o $(TARGERDIR)$(TARGET)

clean:
	rm $(TARGERDIR)*.o