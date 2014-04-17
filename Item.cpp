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

void Item::printColumns(std::ostream &os)
{
    os << setw(COLUMN_WIDTH_SMALL) << left << "ID" << setw(COLUMN_WIDTH_LARGE) << left << "Title" << setw(COLUMN_WIDTH_SMALL) << left << "Type" << setw(COLUMN_WIDTH_LARGE) << left << "Due Date" << setw(COLUMN_WIDTH_SMALL) << left << "Patron" << endl;
}

string Item::formattedDueDate()
{
    char buff[20];
    time_t t_due_date = this->due_date;
    strftime(buff, 20, "%m/%d/%Y %I:%M %p", localtime(&t_due_date));
    
    return buff;
}

Shared_item Item::readFromStream(std::istream &is)
{
    char c;
    is.get(c);
    is.putback(c);
    
    if (c == '\0')
        return nullptr;
    
    string input;
    Shared_item item{ new Item()};
    
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

    item->self = item;
    
    return item;
}

bool Item::writeToStream(std::ostream &os)
{
    os << id << ',' << title << ',' << type << ',' << due_date << ',' <<  patron_id << std::endl;
    
    return os.good();
}

CheckOutStatus Item::checkOut(Patron& p) 
{
    p.addItem(self);

    patron_id = p.getId();

//enum ItemType { ItemTypeAdultBook, ItemTypeChildBook, ItemTypeVideoTape, ItemTypeDVD };
    due_date = time(NULL) + 2 * 24 * 60 * 60;

    return CheckOutStatusSuccess;
}

CheckInStatus Item::checkIn(Patron p) {
    return CheckInStatusError;
}
