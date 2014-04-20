#include <iostream>
#include <sstream>
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


struct Command
{
    string text;
    string arg1;
    string arg2;
};

Library *lib;

Command parse_line(string line)
{
    Command c;
    stringstream ss{line};
    ss >> c.text;
    ss >> c.arg1;
    ss >> c.arg2;

    return c;
}

int parse_id(string text)
{
    int result = -1;
    
    if (!text.empty())
    {
        try
        {
            result = stoi(text);
        }
        catch (...)
        {
            cout << "Invalid id specified: " << text << endl;
        }
    }

    return result;
}

void prompt(string text)
{
    cout << "[" << Date::Instance().TodaysDateIs() << "]" << endl;
    cout << text << ": ";
}

void print_request_patron_id_help() 
{
    cout << tab << "<patron_id> or <command>" << endl;
    cout << tab << tab << "list (display a list of patrons)" << endl;
    cout << tab << tab << "help (display this screen)" << endl;
    cout << tab << tab << "cancel (abort this operation)" << endl;
}

void print_request_item_id_help() 
{
    cout << tab << "<item_id> or <command>" << endl;
    cout << tab << tab << "list (display a list of items)" << endl;
    cout << tab << tab << "help (display this screen)" << endl;
    cout << tab << tab << "cancel (abort this operation)" << endl;
}

void print_list_help() 
{
    cout << tab << "list [sub-command]" << endl;
    cout << tab << tab << "items (list all items)" << endl;
    cout << tab << tab << "patron (list all patron items)" << endl;
    cout << tab << tab << "overdue (list all over due items)" << endl;
}

void print_help() 
{
    cout << endl;
    cout << "usage: <command> [sub-commands, ...]" << endl;
    cout << tab << "checkin [item_id] (Checkin an item)" << endl;
    cout << tab << "checkout [patron_id] [item_id] (Checkout an item to a patron)" << endl;
    print_list_help();
    cout << tab << "advance_date [number_of_days] (simulate future date)" << endl;
    cout << tab << "quit" << endl;
}

int request_patron_id() 
{
    print_request_patron_id_help();

    int pid = -1;

    while (pid < 0)
    {
        prompt("Please enter the Patron's ID");

        string line;
        if ( getline(cin, line) )
        {
            Command cmd = parse_line(line);

            if (cmd.text == "help")
                print_request_patron_id_help();
            else if (cmd.text == "list")
                lib->listAllPatrons(cout);
            else if (cmd.text == "cancel")
                throw user_abort();
            else
                pid = parse_id(cmd.text);
        }
    }

    return pid;
}

int request_item_id(bool checkedOut)
{
    print_request_item_id_help();

    int iid = -1;

    while (iid < 0)
    {
        prompt("Please enter the Item's ID");
        
        string line;
        if( getline(cin, line) )
        {
            Command cmd = parse_line(line);

            if (cmd.text == "help")
                print_request_item_id_help();
            else if (cmd.text == "list")
                lib->listItems(cout, checkedOut?ItemSearchCheckedOut:ItemSearchCheckedIn);
            else if (cmd.text == "cancel")
                throw user_abort();
            else
                iid = parse_id(cmd.text);
        }
    }

    return iid;
}

void listPatronsBooks()
{
    int pid = request_patron_id();

    lib->listPatronItems(cout, pid);
}

void checkout(string patron_id, string item_id)
{
    int pid = parse_id(patron_id);
    if (pid == -1) 
        pid = request_patron_id();
    
    int iid = parse_id(item_id);
    if (iid == -1)
        iid = request_item_id(false);
    
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
    int iid = parse_id(item_id);
    
    if (iid == -1)
        iid = request_item_id(true);

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


void advanceDate()
{
    cout << "\ntoday is: " << Date::Instance().TodaysDateIs() << endl;
	cout <<"How many days would you like to advance:  ";
	
	string days;
    
    if ( getline(cin, days) ) {
        Date::Instance().AdvanceDate(stoi(days));
    } else {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        advanceDate();
    }
    
	cout << "today is now: " << Date::Instance().TodaysDateIs() << endl;
};

LibraryCommand getCommand() {
    cout << endl;
    prompt("Enter a command");
    
    string command;
    
    if ( getline(cin, command) )
    {
        Command cmd = parse_line(command);

        if (cmd.text == "checkin") {
            checkin(cmd.arg1);
            return LibraryCommandCheckIn;
        } else if (cmd.text == "checkout") {
            checkout(cmd.arg1, cmd.arg2);
            return LibraryCommandCheckOut;
        } else if (cmd.text == "list") {
            list(cmd.arg1);
            return LibraryCommandList;
        } else if (command.find("advance_date") != string::npos) {
            advanceDate();
            return LibraryCommandAdvanceDate;
        } else if (cmd.text == "quit" || cmd.text == "q") {
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
