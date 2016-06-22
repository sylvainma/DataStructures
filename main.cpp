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
#include "BST.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    /*
    List<int> liste1;
    liste1.push_back(6);
    liste1.push_back(2);
    liste1.push_back(18);
    liste1.push_back(9);
    liste1.push_back(5);
    liste1.push_back(10);
    cout<<liste1<<endl;
    
    liste1.sort(0);
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
     */
    
    BST<int> abr;
    abr.insert(2);
    abr.insert(5);
    abr.insert(6);
    abr.insert(4);
    abr.insert(1);
    abr.insert(9);
    
    abr.remove(5);
    
    BST<int>::Node* n = abr.search(4);
    if(n!=nullptr)
        cout<<n->getKey()<<endl;
    else
        cout<<"nullptr"<<endl;
    
    cout<<endl;
    
    abr.print();
    
    
    return 0;
}
