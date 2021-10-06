FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default: sqlite3.o
	g++ $(FLAGS) -c Database.cpp

sqlite3.o:
	gcc -O2 -c sqlite-amalgamation-3360000/sqlite3.c

