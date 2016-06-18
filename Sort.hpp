//
//  Sort.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef Sort_hpp
#define Sort_hpp
#include <iostream>

template<class T>
class List;

template<class T>
class Sort {
public:
    virtual void sort(List<T>& L) const=0;
    virtual ~Sort(){}
};

/*
 *  Sort by insertion
 */
template<class T>
class Insertion : public Sort<T> {
public:
    void sort(List<T>& L) const {
        
        unsigned int n=L.size();
        
        // From first one to penultimate
        for(unsigned int i=0; i<n-1; i++) {
            
            unsigned int min=i;
            
            // Compare each other one to find the minimum
            for(unsigned int j=i+1; j<n; j++) {
                if(L[j]<L[min]) min=j;
            }
            
            // Swap the minium found to current place i
            if(i!=min) {
                T tmp = L[i];
                L[i] = L[min];
                L[min] = tmp;
            }
            
        }
        
    }
};

/*
 *  Bubble sort
 */
template<class T>
class Bubble : public Sort<T> {
public:
    void sort(List<T>& L) const {
        
        unsigned int n=L.size();
        
        // For each element of the list, excepted the last one
        for(unsigned int i=0; i<n-1; i++) {
            
            // Swap consecutives elements if needed to
            // put the minimum at the ith position
            for(unsigned int j=n-1; j>i; j--) {
                
                // if right one is lower than left one
                if(L[j]<L[j-1]) {
                    
                    // Shift minimum to the left
                    T tmp = L[j];
                    L[j] = L[j-1];
                    L[j-1] = tmp;
                }
                
            }
            
        }
        
    }
};

#endif /* Sort_hpp */
