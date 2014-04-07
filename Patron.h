//
//  Patron.h
//  Library
//
//  Created by Kody Holman on 4/1/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef __Library__Patron__
#define __Library__Patron__

#include <iostream>
#include <string>
#include <memory>
#include "HelperMethods.h"

class Patron;

typedef std::unique_ptr<Patron> Unique_patron;

class Patron {
    int id;
    std::string first;
    std::string last;
    bool child;
    
public:
    static Patron* readFromStream(std::istream &is);
    bool writeToStream(std::ostream &os);
    
    friend std::ostream& operator<<(std::ostream &os, Patron &p)
    {
        return os << p.id << tab << p.first << tab << p.last << tab << p.child << std::endl;
    }
};

#endif /* defined(__Library__Patron__) */
