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


int Item::getId()
{
    return id;
}

bool Item::isOverdue()
{
    time_t now = time(NULL);

    return patron_id != 0 && due_date < now;
}

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
    item->type = (ItemType)atoi(input.c_str());
    
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

CheckOutStatus Item::checkOut(Unique_patron& p) 
{
    if (patron_id != 0)
        return CheckOutStatusAlreadyCheckedOut;

    CheckOutStatus status = p->addItem(self);

    if (status != CheckOutStatusSuccess)
        return status;

    patron_id = p->getId();
    
    int days = 0;

    switch (type)
    {
        case ItemTypeAdultBook:
            days = 2 * 7;
            break;
        case ItemTypeChildBook:
            days = 7;
            break;
        case ItemTypeVideoTape:
            days = 3;
            break;
        case ItemTypeDVD:
            days = 2;
            break;
        default:
            throw logic_error("Item Type Is NOT recognized.");
    }

    due_date = time(NULL) + days * 24 * 60 * 60;

    return CheckOutStatusSuccess;
}

CheckInStatus Item::checkIn(Unique_patron& p) 
{
    if (patron_id == 0)
        return CheckInStatusAlreadyCheckedIn;

    CheckInStatus status = p->removeItem(self->id);

    if (status != CheckInStatusSuccess)
        return status;

    patron_id = 0;

    if (due_date < time(NULL))
        return CheckInStatusLate;

    return CheckInStatusSuccess;
}
