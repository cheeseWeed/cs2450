//
//  Item.h
//  Library
//
//  Created by Kody Holman on 4/7/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef __Library__Item__
#define __Library__Item__

#include <iostream>
#include "Patron.h"

enum ItemType { ItemTypeAdultBook, ItemTypeChildBook, ItemTypeVideoTape, ItemTypeDVD };
enum CheckInStatus { CheckInStatusOnTime, CheckInStatusLate, CheckInStatusError };
enum CheckOutStatus { CheckOutStatusSuccess, CheckOutStatusTooManyBooks, CheckOutStatusAdultContent, CheckOutStatusError };

class Item;

typedef std::shared_ptr<Item> Shared_item;

class Item {

    Shared_item self;

    int id;
    std::string title;
    int type;
    time_t due_date;
    int patron_id; // patron who checked out book
    
public:

    int getId() { return id; }

    int getPatronId() { return patron_id; }

    static Shared_item readFromStream(std::istream &is);

    bool writeToStream(std::ostream &os);

    CheckOutStatus checkOut(Patron& p);

    CheckInStatus checkIn(Patron p);
    
    friend std::ostream& operator<<(std::ostream &os, Item &item)
    {
        return os << item.id << tab << item.title << tab << item.type << tab << item.due_date << tab << item.patron_id << std::endl;
    }
};

#endif /* defined(__Library__Item__) */

