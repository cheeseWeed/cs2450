#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#include "Library.h"
#include "Date.h"
#include "Constants.h"

using namespace std;

class user_abort : public runtime_error
{
public: 
    
    user_abort() : runtime_error("User aborted operation") {}
};

Library *lib;

int requestPatronId()
{
    int pid = -1;

    while (pid < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        cout << "Please enter the Patron's ID (-1: list, -2: cancel): ";
        if (cin >> pid)
        {
            if (pid == -1) {
                lib->listAllPatrons(cout);
            }
            else if (pid == -2) {
                throw user_abort();
            }
            else if (!lib->validPatronId(pid)) {
                cout << "Invalid Patron ID specified." << endl;
                pid = -1;
            }
        }
    }

    return pid;
}

int requestItemId(bool checkedOut)
{
    int iid = -1;

    while (iid < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        cout << "Please enter the Item's ID (-1: list, -2: cancel): ";
        if(cin >> iid)
        {
            if (iid == -1) {
                lib->listItems(cout, checkedOut?ItemSearchCheckedOut:ItemSearchCheckedIn);
            }
            else if (iid == -2) {
                throw user_abort();
            }
            else if (!lib->validItemId(iid)) {
                cout << "Invalid Item ID specified." << endl;
                iid = -1;
            }
        }
    }

    return iid;
}

void listPatronsBooks()
{
    int pid = requestPatronId();

    lib->listPatronItems(cout, pid);
}

void checkout()
{
    int pid = requestPatronId();
    int iid = requestItemId(false);

    CheckOutStatus status = lib->checkout(pid, iid);

    switch (status)
    {
        case CheckOutStatusSuccess:
            cout << "Checkout completed successfully." << endl;
            break;
        case CheckOutStatusTooManyBooks:
            cout << "Checkout failed -- Patron has exceeded his/her check out limit." << endl;
            break;
        case CheckOutStatusAdultContent:
            cout << "Checkout failed -- Patron is not allowed to check out adult content." << endl;
            break;
        case CheckOutStatusAlreadyCheckedOut:
            cout << "Checkout failed -- The specified item is already checked out." << endl;
            break;
        default:
            throw logic_error("Invalid CheckOutStatus Returned.");
    }
}

void checkin()
{
    int iid = requestItemId(true);

    CheckInStatus status = lib->checkin(iid);

    switch (status)
    {
        case CheckInStatusSuccess:
            cout << "Checkin completed successfully." << endl;
            break;
        case CheckInStatusLate:
            cout << "Warning: Item was returned late." << endl;
            break;
        case CheckInStatusAlreadyCheckedIn:
            cout << "Checkin failed -- The specified item is not checked out." << endl;
            break;
        default:
            throw logic_error("Invalid CheckInStatus Returned.");
    }
}

void mainMenu()
{
    bool quit = false;

    while (!quit)
    {
        try
        {
            cout << endl << "Main Menu:" << endl;
            cout << tab << "1) Checkout a book." << endl;
            cout << tab << "2) Checkin a book." << endl;
            cout << tab << "3) List overdue books." << endl;
            cout << tab << "4) List patron's books." << endl;
            cout << tab << "5) List all books and media." << endl;
            cout << tab << "6) Advance the date." << endl;
            cout << tab << "q) Quit." << endl << endl;
            
            char input = '0';

            cin >> input;
            
            switch (input) {
                case '1':
                    checkout();
                    break;
                case '2':
                    checkin();
                    break;
                case '3':
                    lib->listItems(cout, ItemSearchOverdue);
                    break;
                case '4':
                    listPatronsBooks();
                    break;
                case '5':
                    lib->listItems(cout, ItemSearchAll);
                    break;
                case '6':
                    Date::Instance().AdvanceDate();
                    break;
                case 'q':
                case 'Q':
                    quit = true;
                    break;
                default:
                    cout << "Please choose an option 1-6. or q" << endl;
                    break;
            }

            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (exception &ex)
        {
            cout << ex.what();
        }
    }
};

int main (int argc, const char * argv[]) {

    try
    {

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
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
    
    delete lib;
    
	return 0;
}
