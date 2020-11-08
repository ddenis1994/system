cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(home1 main.cpp cpp/Session.cpp header/Session.h cpp/Graph.cpp header/Graph.h cpp/Agent.cpp header/Agent.h cpp/Tree.cpp header/Tree.h header/BFS.h cpp/BFS.cpp)