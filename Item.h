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
#include <iomanip>
#include "Patron.h"
#include "Constants.h"
#include "Date.h"

#define COLUMN_WIDTH_SMALL 7
#define COLUMN_WIDTH_LARGE 20

class Item;

typedef std::shared_ptr<Item> Shared_item;

class Item : public std::enable_shared_from_this<Item>
{
    int id;
    std::string title;
    ItemType type;
    time_t due_date;
    int patron_id; // patron who checked out book

    Item() = default;

    Item(const Item&) = delete;

    Item& operator=(const Item&) = delete;
    
public:

    int getId();

    int getPatronId() { return patron_id; }

    ItemType getType() { return type; }

    bool isOverdue();

    static void printColumns(std::ostream &os);

    static Shared_item readFromStream(std::istream &is);

    bool writeToStream(std::ostream &os);

    CheckOutStatus checkOut(Unique_patron& p);

    CheckInStatus checkIn(Unique_patron& p);
    
    friend std::ostream& operator<<(std::ostream &os, Item &item)
    {
        os << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.id;
        
        size_t titleLength = COLUMN_WIDTH_LARGE+COLUMN_WIDTH_LARGE+COLUMN_WIDTH_SMALL;
        std::string title = item.title;
        if (title.length() > titleLength-1) {
            title = title.substr(0, titleLength-4) + "...";
        }
        os << std::setw(titleLength) << std::left << title;
        
        os << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.type;
        
        os << std::setw(COLUMN_WIDTH_LARGE) << std::left << Date::Instance().convertTime_tToString(item.due_date);
        
        os << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.patron_id;
        
        return os << std::endl;
    }
};

#endif /* defined(__Library__Item__) */

