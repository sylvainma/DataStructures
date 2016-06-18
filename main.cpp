//
//  main.cpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#include <iostream>
#include "List.hpp"
#include "Stack.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    List<int> liste1;
    liste1.push_back(1);
    liste1.push_back(2);
    liste1.push_back(3);
    liste1.push_back(4);
    liste1.push_back(5);
    liste1.push_back(6);
    cout<<liste1<<endl;
    
    Stack<int> stack;
    stack.push(7);
    stack.push(8);
    stack.push(9);
    stack.push(10);
    stack.push(11);
    stack.push(12);
    
    while(!stack.empty()) {
        cout<<stack.top()<<endl;
        stack.pop();
    }
    
    return 0;
}
