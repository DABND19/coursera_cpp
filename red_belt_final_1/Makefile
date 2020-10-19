CC=g++
FLAGS=-std=c++17

all: search

search: main.o parse.o search_server.o test_runner.h profile.h iterator_range.h
	$(CC) $(FLAGS) -o search main.o parse.o search_server.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

parse.o: parse.h parse.cpp
	$(CC) $(FLAGS) -c parse.cpp

search_server.o: search_server.h search_server.cpp
	$(CC) $(FLAGS) -c search_server.cpp

test: search
	./search

clean:
	rm -rf *.o search
