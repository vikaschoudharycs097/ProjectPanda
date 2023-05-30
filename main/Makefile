# Compiler
CC = g++

# Compiler Flags
FLAGS = -std=c++2a -Wall -Werror -Wpedantic 

Editor: main.o Editor.o
	$(CC) $(FLAGS) -o Editor main.o Editor.o

main.o: ./src/main.cpp
	$(CC) $(FLAGS) -c ./src/main.cpp

Editor.o: ./src/Editor.cpp ./src/Editor.h
	$(CC) $(FLAGS) -c ./src/Editor.cpp