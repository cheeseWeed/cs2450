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

#define COLUMN_WIDTH_ID 7
#define COLUMN_WIDTH_TITLE 27
#define COLUMN_WIDTH_TYPE 10
#define COLUMN_WIDTH_DUE 11

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

    std::string getTypeName();

    bool isOverdue();

    static void printColumns(std::ostream &os);

    static Shared_item readFromStream(std::istream &is);

    bool writeToStream(std::ostream &os);

    CheckOutStatus checkOut(Unique_patron& p);

    CheckInStatus checkIn(Unique_patron& p);
    
    friend std::ostream& operator<<(std::ostream &os, Item &item)
    {
        os << std::setw(COLUMN_WIDTH_ID) << std::left << item.id;
        
        std::string title = trunc(item.title, COLUMN_WIDTH_TITLE);
        os << std::setw(COLUMN_WIDTH_TITLE) << std::left << title;
        
        os << std::setw(COLUMN_WIDTH_TYPE) << std::left << item.getTypeName();
        
        os << std::setw(COLUMN_WIDTH_DUE) << std::left << (item.patron_id == 0?"-":Date::Instance().convertTime_tToString(item.due_date));
        
        std::string status = "In";
        if (item.patron_id != 0)
            status = item.isOverdue()?"LATE":"Out";

        os << status << std::endl;
        
        return os;
    }
};

#endif /* defined(__Library__Item__) */

