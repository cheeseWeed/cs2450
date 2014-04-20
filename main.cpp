#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#include "Library.h"
#include "Date.h"
#include "Constants.h"

using namespace std;

enum LibraryCommand {
    LibraryCommandCheckIn,
    LibraryCommandCheckOut,
    LibraryCommandList,
    LibraryCommandAdvanceDate,
    LibraryCommandQuit,
    LibraryCommandHelp
};

class user_abort : public runtime_error
{
public: 
    
    user_abort() : runtime_error("User aborted operation") {}
};

Library *lib;

void print_list_help() {
    cout << tab << "list [sub-command]" << endl;
    cout << tab << tab << "items (list all items)" << endl;
    cout << tab << tab << "patron (list all patron items)" << endl;
    cout << tab << tab << "overdue (list all over due items)" << endl;
}

void print_help() {
    cout << endl;
    cout << "usage: <command> [sub-commands, ...]" << endl;
    cout << tab << "checkin [item_id] (Checkin an item)" << endl;
    cout << tab << "checkout [patron_id] [item_id] (Checkout an item to a patron)" << endl;
    print_list_help();
    cout << tab << "advance_date [number_of_days] (simulate future date)" << endl;
    cout << tab << "quit" << endl;
}

int requestPatronId()
{
    string patron_id;
    int pid = -1;

    while (pid < 0)
    {
        cout << "Please enter the Patron's ID (-1: list, -2: cancel): ";
        if ( getline(cin, patron_id) )
        {
            pid = stoi(patron_id);
            
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
    string item_id;
    int iid = -1;

    while (iid < 0)
    {
        cout << "Please enter the Item's ID (-1: list, -2: cancel): ";
        if( getline(cin, item_id) )
        {
            iid = stoi(item_id);
            
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

void checkout(string args)
{
    string patron_id = "";
    string item_id = "";
    if (args.find(' ') != string::npos) {
        patron_id = args.substr(0, args.find(' '));
        item_id = args.substr(args.find(' '));
    }
    
    int pid = -1;
    if (patron_id.empty()) {
        pid = requestPatronId();
    } else {
        pid = stoi(patron_id);
    }
    
    int iid = -1;
    if (item_id.empty()) {
        iid = requestItemId(false);
    } else {
        iid = stoi(item_id);
    }
    
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

void checkin(string item_id)
{
    int iid = -1;
    
    if (item_id.empty()) {
        iid = requestItemId(true);
    } else {
        iid = stoi(item_id);
    }

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

void list(string input) {
    string sub_command;
    
    if (!input.empty() )
    {
        if (input == "items") {
            lib->listItems(cout, ItemSearchAll);
        } else if (input == "patron") {
            listPatronsBooks();
        } else if (input == "overdue") {
            lib->listItems(cout, ItemSearchOverdue);
        } else {
            print_list_help();
            cout << "sub-command: ";
            getline(cin, sub_command);
            list(sub_command);
        }
    }
    else
    {
        print_list_help();
        cout << "sub-command: ";
        getline(cin, sub_command);
        list(sub_command);
    }
}

LibraryCommand getCommand() {
    cout << endl << "Enter a command: ";
    
    string command;
    
    if ( getline(cin, command) )
    {
        if (command.find("checkin") != string::npos) {
            checkin(command.substr(command.find(' ')+1));
            return LibraryCommandCheckIn;
        } else if (command.find("checkout") != string::npos) {
            checkout(command.substr(command.find(' ')+1));
            return LibraryCommandCheckOut;
        } else if (command.find("list") != string::npos) {
            list(command.substr(command.find(' ')+1));
            return LibraryCommandList;
        } else if (command.find("advance_date") != string::npos) {
            Date::Instance().AdvanceDate();
            return LibraryCommandAdvanceDate;
        } else if (command.find("quit") != string::npos || command.find("q") != string::npos) {
            return LibraryCommandQuit;
        } else {
            cout << "Please enter a valid command." << endl;
            print_help();
            return LibraryCommandHelp;
        }
    }
    else
    {
        return getCommand();
    }
    
    return LibraryCommandHelp;
};

void mainMenu()
{
    cout << "Welcome to the Library! (enter 'help' to get a list of commands')" << endl;
    
    print_help();
    
    bool quit = false;
    while (!quit)
    {
        try
        {
            if (LibraryCommandQuit == getCommand()) {
                quit = true;
            }
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
