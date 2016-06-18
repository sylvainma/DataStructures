//
//  DSException.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef DSException_hpp
#define DSException_hpp
#include <string>

class DSException {
    std::string message;
public:
    DSException(const std::string msg):message(msg){}
    const std::string& getMessage() const { return message; }
};

#endif /* DSException_hpp */
