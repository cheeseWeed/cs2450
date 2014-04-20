//
//  HelperMethods.h
//  Library
//
//  Created by Kody Holman on 4/7/14.
//  Copyright (c) 2014 Kody Holman. All rights reserved.
//

#ifndef Library_HelperMethods_h
#define Library_HelperMethods_h

//#pragma mark - Helper Methods

#include <ostream>

inline std::ostream& tab(std::ostream& os) {
    return os << '\t';
};

inline std::string trunc(std::string val, size_t length) {
    std::string result = val;

    if (result.length() > length - 1)
        result = result.substr(0, length - 4) + "...";

    return result;
}

#endif
