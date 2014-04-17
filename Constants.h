#ifndef __Library__Constants__
#define __Library__Constants__

enum ItemType 
{ 
    ItemTypeAdultBook, 
    ItemTypeChildBook, 
    ItemTypeVideoTape, 
    ItemTypeDVD 
};

enum CheckInStatus 
{ 
    CheckInStatusSuccess, 
    CheckInStatusLate, 
    CheckInStatusAlreadyCheckedIn 
};

enum CheckOutStatus 
{ 
    CheckOutStatusSuccess, 
    CheckOutStatusTooManyBooks, 
    CheckOutStatusAdultContent, 
    CheckOutStatusAlreadyCheckedOut 
};

enum ItemSearch
{
    ItemSearchAll,
    ItemSearchCheckedOut,
    ItemSearchCheckedIn,
    ItemSearchOverdue
};

#endif /* defined(__Library__Constants__) */

