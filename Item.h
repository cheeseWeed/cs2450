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

#define COLUMN_WIDTH_SMALL 7
#define COLUMN_WIDTH_LARGE 20

enum ItemType { ItemTypeAdultBook, ItemTypeChildBook, ItemTypeVideoTape, ItemTypeDVD };
enum CheckInStatus { CheckInStatusOnTime, CheckInStatusLate, CheckInStatusError };
enum CheckOutStatus { CheckOutStatusSuccess, CheckOutStatusTooManyBooks, CheckOutStatusAdultContent, CheckOutStatusError };

class Item;

typedef std::unique_ptr<Item> Unique_item;

class Item {
    int id;
    std::string title;
    int type;
    int due_date;
    int patron_id; // patron who checked out book
    
public:
    static void printColumns(std::ostream &os);
    std::string formattedDueDate();
    
    static Item* readFromStream(std::istream &is);
    bool writeToStream(std::ostream &os);
    virtual CheckOutStatus checkOut(Patron p);
    CheckInStatus checkIn(Patron p);
    
    friend std::ostream& operator<<(std::ostream &os, Item &item)
    {
        return os << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.id << std::setw(COLUMN_WIDTH_LARGE) << std::left << item.title << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.type << std::setw(COLUMN_WIDTH_LARGE) << std::left << item.formattedDueDate() << std::setw(COLUMN_WIDTH_SMALL) << std::left << item.patron_id << std::endl;
    }
};

#endif /* defined(__Library__Item__) */
