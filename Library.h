//
//  Library.h
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef __Library__Library__
#define __Library__Library__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patron.h"
#include "Item.h"

using namespace std;

class Library {
    string filename;
    vector<Unique_patron> patrons;
    vector<Unique_item> items;
    
private:
    void load();
    void save();
    
public:
    explicit Library(string aFilename);
    ~Library();
    
    bool checkout(Patron patron, Item item);
    bool checkin(Patron patron, Item item);
};

#endif /* defined(__Library__Library__) */
