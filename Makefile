FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default: sqlite3.o
	g++ $(FLAGS) -c Database.cpp
	g++ $(FLAGS) -c Soften.cpp
	ar rcs libTrust.a Database.o Soften.o
	g++ $(FLAGS) -c main.cpp
	g++ -L . -pthread -o main main.o sqlite3.o -lTrust -ldl

sqlite3.o:
	gcc -O2 -c sqlite-amalgamation-3360000/sqlite3.c

