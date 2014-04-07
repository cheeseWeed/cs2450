//
//  Item.cpp
//  Library
//
//  Created by Kody Holman on 4/7/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#include "Item.h"
#include <string>

using namespace std;

Item* Item::readFromStream(std::istream &is)
{
    char c;
    is.get(c);
    is.putback(c);
    
    if (c == '\0')
        return nullptr;
    
    string input;
    Item *item = new Item();
    
    getline(is, input, ',');
    item->id = atoi(input.c_str());
    
    getline(is, input, ',');
    item->title = input.c_str();
    
    getline(is, input, ',');
    item->type = atoi(input.c_str());
    
    getline(is, input, ',');
    item->due_date = atoi(input.c_str());
    
    getline(is, input);
    item->patron_id = atoi(input.c_str());
    
    return item;
}

bool Item::writeToStream(std::ostream &os)
{
    os << id << ',' << title << ',' << type << ',' << due_date << ',' <<  patron_id << std::endl;
    
    return os.good();
}

CheckOutStatus Item::checkOut(Patron p) {
    return CheckOutStatusError;
}

CheckInStatus Item::checkIn(Patron p) {
    return CheckInStatusError;
}