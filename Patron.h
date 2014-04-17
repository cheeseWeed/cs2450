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
#include <string>
#include <memory>
#include "HelperMethods.h"
#include "Constants.h"

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

    bool writeToStream(std::ostream &os);

    CheckOutStatus addItem(std::shared_ptr<Item> item);

    void listItems(std::ostream& os);
    
    friend std::ostream& operator<<(std::ostream &os, Patron &p)
    {
        return os << p.id << tab << p.first << tab << p.last << tab << p.child << std::endl;
    }
};

#endif /* defined(__Library__Patron__) */

