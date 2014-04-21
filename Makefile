build: Makefile Date.o Item.o Patron.o Library.o main.cpp
	g++ -g -std=c++11 -Wall Date.o Item.o Patron.o Library.o main.cpp
	mv a.out library

test: Makefile Date.o Item.o Patron.o Library.o test_main.cpp library_file_test.orig
	cp library_file_test.orig library_file_test.ldb
	g++ -g -std=c++11 -Wall Date.o Item.o Patron.o Library.o test_main.cpp
	mv a.out test_library

Library.o: Library.h Library.cpp
	g++ -g -std=c++11 -Wall -c Library.cpp

Patron.o: Patron.h Patron.cpp
	g++ -g -std=c++11 -Wall -c Patron.cpp

Item.o: Item.h Item.cpp
	g++ -g -std=c++11 -Wall -c Item.cpp

Date.o: Date.h Date.cpp
	g++ -g -std=c++11 -Wall -c Date.cpp

clean: 
	rm -f test_library
	rm -f library
	rm -rf *.dSYM
	rm -rf *.o
