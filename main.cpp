#include <iostream>
#include <string>
#include "Library.h"

using namespace std;

void mainMenu()
{
    cout << "Main Menu:" << endl;
    cout << tab << "1) Checkout a book." << endl;
    cout << tab << "2) Checkin a book." << endl;
    cout << tab << "3) List overdue books." << endl;
    cout << tab << "4) List patron's books." << endl;
    
    char num = '0';
    cin.get(num);
    
    cout << num << endl;
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
    
    Library lib(filename);
    
    mainMenu();
    
	return 0;
}