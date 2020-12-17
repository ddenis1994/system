# the compiler: gcc for C program, define as g++ for C++
CC = g++

    # compiler flags:
    #  -g    adds debugging information to the executable file
    #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Weffc++ -std=c++11
TARGET = cTrace
TARGERDIR=bin/

all: clean Graph Session Agent Tree main target


Graph: src/Graph.cpp src/Graph.h
	$(CC) $(CFLAGS) -c src/Graph.cpp -o $(TARGERDIR)Graph.o

Session: src/Session.h src/Session.cpp
	$(CC) $(CFLAGS) -c src/Session.cpp -o $(TARGERDIR)Session.o

Agent: include/Agent.h src/Agent.cpp
	$(CC) $(CFLAGS) -c src/Agent.cpp -o $(TARGERDIR)Agent.o

Tree: include/Tree.h src/Tree.cpp
	$(CC) $(CFLAGS) -c src/Tree.cpp -o $(TARGERDIR)Tree.o

main: src/main.cpp
	$(CC) $(CFLAGS) -c -c src/main.cpp -o $(TARGERDIR)main.o

target : $(TARGERDIR)Agent.o $(TARGERDIR)Graph.o $(TARGERDIR)Session.o $(TARGERDIR)Tree.o $(TARGERDIR)main.o
	$(CC) $(CFLAGS) $(TARGERDIR)Agent.o $(TARGERDIR)Graph.o $(TARGERDIR)Session.o $(TARGERDIR)Tree.o $(TARGERDIR)main.o -o $(TARGERDIR)$(TARGET)

clean:
	rm $(TARGERDIR)*.o