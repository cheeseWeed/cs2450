//
//  Library.cpp
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#define PAT_ID "#PAT"
#define ITEM_ID "#ITEM"

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "Library.h"

using namespace std;

//#pragma mark - Constructor/Destructor
Library::Library(string aFilename)
    : filename(aFilename)
{
    this->load();
}

Library::~Library()
{
    this->save();
}

Unique_patron& Library::getPatron(int patronId)
{
    auto patronIter = find_if(patrons.begin(), patrons.end(), [patronId](Unique_patron& p){ return p->getId() == patronId;});
    
    if (patronIter == patrons.end())
        throw logic_error("Invalid patron identifier specified.");

    return *patronIter;
}

Shared_item& Library::getItem(int itemId)
{
    auto itemIter = find_if(items.begin(), items.end(), [itemId](Shared_item& i){ return i->getId() == itemId;});

    if (itemIter == items.end())
        throw logic_error("Invalid item identifier specified.");

    return *itemIter;
}

//#pragma mark - Private Methods
void Library::load()
{
    fstream file(filename, ios_base::in);
    string input;
    
    getline(file, input);
    if (input.find(PAT_ID) == string::npos) {
        throw runtime_error("ERROR: file not correct format.");
    }
    while ( file ) {
        Patron *p = Patron::readFromStream(file);
        if (p == nullptr)
            break;

        patrons.push_back( Unique_patron(p) );
    }
    
    getline(file, input);
    if (input.find(ITEM_ID) == string::npos) {
        throw runtime_error("ERROR: file not correct format.");
    }
    while ( file ) {
        Shared_item item = Item::readFromStream(file); 
        if (item == nullptr)
            break;
        
        items.push_back( item );

        int pid;
        if ((pid = item->getPatronId()) != 0)
        {
            auto &patron = getPatron(pid);
            patron->addItem(item);
        }
    }
    
    file.close();
}

void Library::save()
{
    fstream file(filename, ios_base::trunc);
    
    file.seekg(0, file.beg);
    
    file << PAT_ID << endl;
    for (auto &p: patrons) {
        p->writeToStream(file);
    }
    
    file << ITEM_ID << endl;
    for (auto &item: items) {
        item->writeToStream(file);
    }
    
    cout << "Saved '" << filename << "'." << endl;
    
    file.close();
}

void Library::listAllItems(ostream &os) {
    Item::printColumns(os);
    
    for (auto &item: items) {
        os << *item;
    }
}

void Library::listPatronItems(ostream &os, int patronId)
{
    auto &patron = getPatron(patronId);

    patron->listItems(os);
}

bool Library::checkout(int patronId, int itemId)
{
    auto &patron = getPatron(patronId);
    auto &item = getItem(itemId);

    item->checkOut(patron);

    return true;
}

bool Library::checkin(int patrongId, int itemId)
{
    return true;
}
