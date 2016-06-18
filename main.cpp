//
//  main.cpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#include <iostream>
#include "List.hpp"

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
    
    List<int> liste2;
    liste2.push_back(7);
    liste2.push_back(8);
    liste2.push_back(9);
    liste2.push_back(10);
    liste2.push_back(11);
    liste2.push_back(12);
    cout<<liste2<<endl;
    
    liste1=liste2;
    cout<<liste1<<endl;
    cout<<liste2<<endl;
    
    return 0;
}
