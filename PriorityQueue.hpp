//
//  PriorityQueue.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 22/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp
#include "List.hpp"

/*
 *  Priority queue (max)
 *  2-ary heap implementation
 */
template<class T>
class PriorityQueue {
    
    /*
     *  Heap for the priority queue
     */
    List<T> heap;
    
public:
    
    /*
     *  Init an empty priority queue
     */
    PriorityQueue(){}
    
    /*
     *  Init a priority queue with a list
     */
    PriorityQueue(const List<T> h):heap(h){ constuct(heap); }
    
    /*
     *  Construct a heap, heapify the whole list 
     *  O(h)
     */
    void constuct(List<T>& L);
    
    /*
     *  Heapify a list from index i 
     *  O(h)
     */
    void heapify(List<T>& L, unsigned int i) const;
    
    /*
     *  Heap sort (return a sorted copy)
     *  O(n*h) (h=log_2(n) if eq tree)
     */
    List<T> heapsort() const;
    
    /*
     *  Extract the higher priority (delete it from the heap)
     *  O(h)
     */
    T extract();
    
    /*
     *  Insert a new key into the priority queue
     */
    void insert(T t);
    
    /*
     *  Get sons and father index in the heap
     */
    unsigned int father(unsigned int i) const { return (i-1)/2; }
    unsigned int left(unsigned int i) const { return 2*i+1; }
    unsigned int right(unsigned int i) const { return 2*i+2; }
    
    /*
     *  Size & length of the heap
     */
    unsigned int size() const { return heap.size(); }
    unsigned int length() const { return heap.length(); }
    
    /*
     *  Print the priority queue
     */
    void print(std::ostream& f=std::cout) const;
    
};

template<class T>
void PriorityQueue<T>::constuct(List<T>& L) {
    
    // From the first father up to the root,
    // each sub-tree is heapified: so that the
    // priority max at each step is pulled up
    // So at each step, the sub-tree is a heap
    for(int i=father(size()); i>=0; i--)
        heapify(heap, i);
    
}

template<class T>
void PriorityQueue<T>::heapify(List<T>& L, unsigned int i) const {
    
    //  Guess that left and right sons are heap,
    //  we then turn father node (index i), left (l)
    //  and right (r) heap into a global heap
    
    unsigned int l=left(i);
    unsigned int r=right(i);
    unsigned int max;
    
    // Check if l exists (l is lower than size of L)
    // and store index of the max key between father and left
    if(l<L.size() && L[l]>L[i])
        max=l;
    else
        max=i;
    
    // Check if r exists (r is lower than size of L)
    // and store index of the max key betwwen current max and right
    if(r<L.size() && L[r]>L[max])
        max=r;
    
    // Swap the max with the father and then heapify if
    // it's necessary (if max has been found in left or right sons)
    if(max!=i) {
        // Swap father and max
        L.swap(i,max);
        // Recall to heapify the transformed list
        heapify(L, max);
    }
    
}

template<class T>
List<T> PriorityQueue<T>::heapsort() const {
    if(size()>0) {
        
        // Make a copy of the heap (because it will be empty root after root)
        List<T> copy=heap;
        
        // List we fill root after root and return at the end
        List<T> res;
        
        // Each iteration, the higher priority is at root
        // So we swap it with lower priority (last leaf),
        // and then we heapify the new tree, we can repeat it
        // for each element.
        // Finally we get a list in ascending order (higher
        // priority at the end).
        for(unsigned int i=size()-1; i>=1; i--) {
            // Swap the root and the ith element
            copy.swap(i,0);
            // Insert into the result list
            res.push_back(copy[i]);
            // Pop the root we just inserted in the sorted result list
            copy.pop_back();
            // Heapify the new tree to get the higher priority at root
            heapify(copy,0);
        }
        
        // Add last root
        res.push_back(copy[0]);
        
        // Return sorted copy
        return res;
        
    }
    else throw DSException("The priority queue is empty");
}

template<class T>
T PriorityQueue<T>::extract() {
    if(size()>0) {
        T max = heap[0];
        heap.swap(0,size()-1);
        heap.pop_back();
        heapify(heap, 0);
        return max;
    }
    else throw DSException("The priority queue is empty");
}

template<class T>
void PriorityQueue<T>::insert(T t) {
    heap.push_back(t);
    unsigned int i=size()-1;
    while(i>0 && heap[father(i)]<t) {
        std::cout<<"boucle"<<std::endl;
        heap.swap(i, father(i));
        i=father(i);
    }
}

template<class T>
void PriorityQueue<T>::print(std::ostream& f) const {
    for(typename List<T>::const_iterator it=heap.cbegin(); it!=heap.cend(); ++it)
        f<<*it<<" ";
    f<<std::endl;
}

#endif /* PriorityQueue_hpp */
