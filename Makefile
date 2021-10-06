FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default:
	g++ $(FLAGS) -c Database.cpp
	gcc -O2 -c sqlite-amalgamation-3360000/sqlite3.c
