#include <iostream>
#include <string>
#include <stdexcept>
#include "Library.h"
#include "Date.h"

using namespace std;

Library *lib;
Date *date;


void mainMenu()
{
    cout << "Main Menu:" << endl;
    cout << tab << "1) Checkout a book." << endl;
    cout << tab << "2) Checkin a book." << endl;
    cout << tab << "3) List overdue books." << endl;
    cout << tab << "4) List patron's books." << endl;
    cout << tab << "5) List all books and media." << endl;
	cout << tab << "6) Advance the date." << endl;
    cout << tab << "q) Quit." << endl << endl;
    
    char input = '0';
    cin.get(input);
    cin.get(); // '\n'
    
    switch (input) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            lib->listAllItems(cout);
            break;
		case '6':
			break;
        case 'q':
        case 'Q':
            return;
        default:
            cout << "Please choose an option 1-5." << endl;
            break;
    }
    
    mainMenu();
};

int main (int argc, const char * argv[]) {
    if (argc < 2) // expecting './library library_file.ldb'
    {
        throw runtime_error("ERROR: Must provide file path to library.");
    }
    
    string filename = argv[1];
    
    if (filename.find(".ldb") == string::npos) {
        throw runtime_error("ERROR: Must provide .ldb filetype.");
    }
    
    lib = new Library(filename);
    
    mainMenu();
    
    delete lib;
    
	return 0;
}