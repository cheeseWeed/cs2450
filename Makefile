build: Makefile Item.o Patron.o Library.o main.cpp
	g++ -g -stdlib=libc++ -std=c++11 Item.o Patron.o Library.o main.cpp
	mv a.out library

test: Makefile Item.o Patron.o Library.o test_main.cpp
	g++ -g -stdlib=libc++ -std=c++11 Item.o Patron.o Library.o test_main.cpp
	mv a.out test_library

Library.o: Library.h Library.cpp
	g++ -g -stdlib=libc++ -std=c++11 -c Library.cpp
    
Patron.o: Patron.h Patron.cpp
	g++ -g -stdlib=libc++ -std=c++11 -c Patron.cpp
    
Item.o: Item.h Item.cpp
	g++ -g -stdlib=libc++ -std=c++11 -c Item.cpp

clean: 
	rm -f test_library
	rm -f library
	rm -rf *.dSYM
	rm -r *.o
