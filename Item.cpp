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

string Item::getTypeName()
{
    string result;

    switch (type)
    {
        case ItemTypeAdultBook:
            result = "Book";
            break;
        case ItemTypeChildBook:
            result = "Kids Book";
            break;
        case ItemTypeVideoTape:
            result = "VHS";
            break;
        case ItemTypeDVD:
            result = "DVD";
            break;
    }

    return result;
}

bool Item::isOverdue()
{
    time_t now = Date::Instance().TodayIs();

    return patron_id != 0 && due_date < now;
}

void Item::printColumns(std::ostream &os)
{
    os << setw(COLUMN_WIDTH_ID) << left << "ID";
    os << setw(COLUMN_WIDTH_TITLE) << left << "Title";
    os << setw(COLUMN_WIDTH_TYPE) << left << "Type";
    os << setw(COLUMN_WIDTH_DUE) << left << "Due Date";
    os << "Status" << endl;
}

Shared_item Item::readFromStream(std::istream &is)
{
    string input;
    Shared_item item{ new Item()};
    
    getline(is, input, ',');
    
    if (input.empty())
        return nullptr;
    
    item->id = atoi(input.c_str());
    
    getline(is, input, ',');
    item->title = input.c_str();
    
    getline(is, input, ',');
    item->type = (ItemType)atoi(input.c_str());
    
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

CheckOutStatus Item::checkOut(Unique_patron& p) 
{
    if (patron_id != 0)
        return CheckOutStatusAlreadyCheckedOut;

    CheckOutStatus status = p->addItem(shared_from_this());

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

    time_t now = Date::Instance().TodayIs();
    due_date = now + days * 24 * 60 * 60;

    return CheckOutStatusSuccess;
}

CheckInStatus Item::checkIn(Unique_patron& p) 
{
    if (patron_id == 0)
        return CheckInStatusAlreadyCheckedIn;

    CheckInStatus status = p->removeItem(id);

    if (status != CheckInStatusSuccess)
        return status;

    patron_id = 0;

    time_t now = Date::Instance().TodayIs();
    if (due_date < now)
        return CheckInStatusLate;

    return CheckInStatusSuccess;
}
