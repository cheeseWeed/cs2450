//
//  Library.cpp
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#define PAT_ID "#PAT"
#define ITEM_ID "#ITEM"

#include "Library.h"
#include <stdexcept>

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
        Item *item = Item::readFromStream(file); // TODO: How do we determine which object type to use?
        if (item == nullptr)
            break;
        
        items.push_back( Unique_item(item) );
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
    for (auto &item: items) {
        os << *item << endl;
    }
}
