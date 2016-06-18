//
//  Stack.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp
#include "DSException.hpp"
#include "List.hpp"

template<class T>
class Stack : private List<T> {
public:
    // Bases
    const unsigned int size() const { return List<T>::size(); }
    bool empty() const { return List<T>::empty(); }
    bool clear() { List<T>::clear(); return true; }
    
    // Access elements
    T& top() { return List<T>::back(); }
    bool push(T t) { List<T>::push_back(t); return true; }
    bool pop() { List<T>::pop_back(); return true; }
};

#endif /* Stack_hpp */
