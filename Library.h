//
//  Library.h
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef __Library__Library__
#define __Library__Library__

#include <iosfwd>
#include <fstream>
#include <string>
#include <vector>
#include "Patron.h"
#include "Item.h"

class Library {
    std::string filename;
    std::vector<Unique_patron> patrons;
    std::vector<Shared_item> items;

    Unique_patron& getPatron(int patronId);
    Shared_item& getItem(int itemId);
    
    void load();
    void save();
    
public:
    explicit Library(std::string aFilename);
    ~Library();
    
    void listAllItems(std::ostream &os);

    void listPatronItems(std::ostream &os, int patronId);
    
    CheckOutStatus checkout(int patronId, int itemId);

    bool checkin(int patronId, int itemId);
};

#endif /* defined(__Library__Library__) */
