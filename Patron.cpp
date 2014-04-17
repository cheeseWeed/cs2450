//
//  Patron.cpp
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#include <algorithm>
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

CheckOutStatus Patron::addItem(shared_ptr<Item> item)
{
    if (child)
    {
        if(item->getType() != ItemTypeChildBook)
            return CheckOutStatusAdultContent;

        if(items.size() > 2)
            return CheckOutStatusTooManyBooks;
    }
    else if(items.size() > 5)
    {
        return CheckOutStatusTooManyBooks;
    }

    items.push_back(item);

    return CheckOutStatusSuccess;
}

CheckInStatus Patron::removeItem(int itemId)
{
    auto itemIter = find_if(items.begin(), items.end(), [itemId](Shared_item& item){ return item->getId() == itemId; });

    if (itemIter == items.end())
        throw logic_error("User does not have the specified item checked out.");

    items.erase(itemIter);

    return CheckInStatusSuccess;
}


bool Patron::writeToStream(std::ostream &os)
{
    os << id << ',' << first << ',' << last << ',' << child << std::endl;
    
    return os.good();
}

void Patron::listItems(ostream& os)
{
    Item::printColumns(os);

    for (auto &item: items)
        os << *item;
}
