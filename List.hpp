//
//  List.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 18/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef List_hpp
#define List_hpp
#include "DSException.hpp"
#include "Sort.hpp"
#include <iostream>

template<class T>
class List {
    T* list;
    unsigned int nb;
    unsigned int max;
public:
    List():list(nullptr),nb(0),max(0){}
    List(const List<T>& l);
    void operator=(const List<T>& l);
    ~List();
    
    // Bases
    const unsigned int size() const { return nb; }
    bool empty() const { return nb==0; }
    bool resize(const unsigned int n=10);
    bool clear() { nb=0; return true; }
    
    // Access elements
    T& operator[](unsigned int i);
    
    // Container methods
    T& front();
    T& back();
    bool push_front(T t);
    bool push_back(T t);
    bool pop_front();
    bool pop_back();
    
    // Sort
    bool sort(unsigned int  i=0);
    
    // iterator
    class iterator {
        friend class List;
        T* current;
        iterator(T* l):current(l){}
    public:
        iterator& operator++() { current++; return *this; }
        bool operator==(const iterator& it) const { return it.current==current; }
        bool operator!=(const iterator& it) const { return it.current!=current; }
        T& operator*() const { return *current; }
        T* operator->() const { return current; }
    };
    iterator begin() { return iterator(list); }
    iterator end() { return iterator(list+nb); }
    
    // const_iterator
    class const_iterator {
        friend class List;
        T* current;
        const_iterator(T* l):current(l){}
    public:
        const_iterator& operator++() { current++; return *this; }
        bool operator==(const const_iterator& it) const { return it.current==current; }
        bool operator!=(const const_iterator& it) const { return it.current!=current; }
        const T& operator*() const { return *current; }
        const T* operator->() const { return current; }
    };
    const_iterator cbegin() const { return const_iterator(list); }
    const_iterator cend() const { return const_iterator(list+nb); }
    
};

template<class T>
List<T>::List(const List<T>& l):list(nullptr),nb(l.nb),max(l.max) {
    // Allocate and copy the list
    list = new T[l.max];
    for(unsigned int i=0; i<l.nb; i++)
        list[i]=l.list[i];
}

template<class T>
void List<T>::operator=(const List<T>& l) {
    clear();
    for(typename List<T>::const_iterator it=l.cbegin(); it!=l.cend(); ++it)
        push_back(*it);
}

template<class T>
List<T>::~List() {
    // Delete list
    if(max>0) {
        delete[] list;
        list=nullptr;
        nb=0;
        max=0;
    }
    
    // Delete algoSort
    //if(algoSort!=nullptr) delete algoSort;
}

template<class T>
T& List<T>::operator[](unsigned int i) {
    if(i>=nb) throw DSException("Index overflow");
    else return list[i];
}

template<class T>
T& List<T>::front() {
    if(!empty()) return list[0];
    else throw DSException("The list is empty");
}

template<class T>
T& List<T>::back() {
    if(!empty()) return list[nb-1];
    else throw DSException("The list is empty");
}

template<class T>
bool List<T>::resize(const unsigned int n) {
    // Determine the new size:
    // if n is lower than current max, we add n to max
    // else we set max to n
    unsigned int newMax=0;
    if(n<=max) newMax=max+n;
    else newMax=n;
    
    // Generate new list with new size
    T* newList = new T[newMax];
    
    // Fill the new list with current values
    for(unsigned int i=0; i<max; i++)
        newList[i]=list[i];
    
    // Assign new list adress
    T* oldList=list;
    list=newList;
    
    // Delete old list and update size property
    delete[] oldList;
    max=newMax;
    return true;
}

template<class T>
bool List<T>::push_front(T t) {
    if(nb==max) resize();
    
    // Shift all elements
    nb++;
    for(unsigned int i=nb; i>0; i--)
        list[i]=list[i-1];
        
    // Insert new element
    list[0]=t;
    return true;
}

template<class T>
bool List<T>::push_back(T t) {
    if(nb==max) resize();
    list[nb++]=t;
    return true;
}

template<class T>
bool List<T>::pop_front() {
    if(empty()) throw DSException("The list is empty");
    
    // Shift to le left
    for(unsigned int i=0; i<nb-1; i++)
        list[i]=list[i+1];
    
    // Update size
    nb--;
    return true;
}

template<class T>
bool List<T>::pop_back() {
    if(empty()) throw DSException("The list is empty");
    // Update size
    nb--;
    return true;
}

template<class T>
bool List<T>::sort(unsigned int  i) {
    Sort<T>* algoSort;
    switch (i) {
        case 1:
            algoSort=new Bubble<T>;
            break;
        case 2:
            algoSort=new Insertion<T>;
            break;
        case 3:
            algoSort=new Selection<T>;
            break;
        default:
            algoSort=new Quick<T>;
            break;
    }
    algoSort->sort(*this);
    delete algoSort;
    return true;
}

template<class T>
std::ostream& operator<<(std::ostream& f, List<T>& list) {
    for(typename List<T>::const_iterator it=list.cbegin(); it!=list.cend(); ++it)
        f<<*it<<"\n";
    return f;
}

#endif /* List_hpp */
