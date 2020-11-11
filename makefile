all:
	rm -f bin/*
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o cpp/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BFS.o cpp/BFS.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o cpp/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o cpp/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o cpp/Tree.cpp
	g++ -o bin/file bin/main.o bin/Agent.o bin/BFS.o bin/Graph.o bin/Session.o bin/Tree.o