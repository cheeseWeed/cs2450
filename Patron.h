//
//  Patron.h
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef __Library__Patron__
#define __Library__Patron__

#include <vector>
#include <iosfwd>
#include <iomanip>
#include <string>
#include <memory>
#include "HelperMethods.h"
#include "Constants.h"

#define COLUMN_WIDTH_ID 7
#define COLUMN_WIDTH_NAME 20

class Patron;
class Item;

typedef std::unique_ptr<Patron> Unique_patron;

class Patron {

    std::vector<std::shared_ptr<Item>> items;

    int id;
    std::string first;
    std::string last;

    Patron() = default;

    Patron(const Patron&) = delete;
    
    Patron& operator=(const Patron&) = delete;
    
public:

    int getId();

    bool child;
    
    static Patron* readFromStream(std::istream &is);

    static void printColumns(std::ostream &os);

    bool writeToStream(std::ostream &os);

    CheckOutStatus addItem(std::shared_ptr<Item> item);

    CheckInStatus removeItem(int itemId);

    void listItems(std::ostream& os);
    
    friend std::ostream& operator<<(std::ostream &os, Patron &p)
    {
        os << std::setw(COLUMN_WIDTH_ID) << std::left << p.id;

        std::string name = trunc(p.last + ", " + p.first, COLUMN_WIDTH_NAME);

        os << std::setw(COLUMN_WIDTH_NAME) << std::left << name;
        
        os << (p.child?"Child":"Adult") << std::endl;

        return os;
    }
};

#endif /* defined(__Library__Patron__) */

