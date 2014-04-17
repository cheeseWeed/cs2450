//
//  Patron.cpp
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include "Patron.h"
#include "Item.h"

using namespace std;

int Patron::getId()
{
    return id;
}

Patron* Patron::readFromStream(std::istream &is)
{
    char c;
    is.get(c);
    is.putback(c);
    
    if (c == '#')
        return nullptr;
    
    string input;
    Patron *p = new Patron();
    
    getline(is, input, ',');
    p->id = atoi(input.c_str());
    
    getline(is, input, ',');
    p->first = input;
    
    getline(is, input, ',');
    p->last = input;
    
    getline(is, input);
    p->child = atoi(input.c_str()) == 1;

    return p;
}

void Patron::addItem(shared_ptr<Item> item)
{
    items.push_back(item);
}

bool Patron::writeToStream(std::ostream &os)
{
    os << id << ',' << first << ',' << last << ',' << child << std::endl;
    
    return os.good();
}

void Patron::listItems(ostream& os)
{
    for (auto &item: items)
        os << *item << endl;
}
