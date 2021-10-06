FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default: sqlite3.o
	g++ $(FLAGS) -c Database.cpp
	g++ $(FLAGS) -c main.cpp
	g++ -pthread -o main main.o sqlite3.o Database.o -ldl

sqlite3.o:
	gcc -O2 -c sqlite-amalgamation-3360000/sqlite3.c

