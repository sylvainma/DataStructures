//
//  BST.hpp
//  DataStructures
//
//  Created by Sylvain Marchienne on 21/06/2016.
//  Copyright © 2016 LO21. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp
#include "List.hpp"

/*
 *  Binary Search Tree
 *  Chained list implementation
 */
template<class T>
class BST {
public:
    /*
     *  Node
     */
    class Node {
        friend class BST;
        
        /*
         *  Store the key of the node
         */
        T key;
        
        /*
         *  Link to the father
         */
        Node* f;
        
        /*
         *  Link to the left son
         */
        Node* l;
        
        /*
         *  Link to the right son
         */
        Node* r;
        
    public:
        Node(T k):key(k),f(nullptr),l(nullptr),r(nullptr){}
        ~Node() { f=nullptr; l=nullptr; r=nullptr; }
        const T& getKey() const { return key; }
        void setKey(T k) { key=k; }
    };
    
private:
    
    /*
     *  Create new empty node
     */
    Node* createNode() { return new Node; }
    
    /*
     *  Create new filled node
     */
    Node* createNode(const T& k) { return new Node(k); }
    
    /*
     *  Root of the tree
     */
    Node* root;
    
public:
    
    /*
     * The BST can be empty at the beginning
     */
    BST():root(nullptr){}
    
    /*
     *  Destructor to delete all the nodes
     */
    ~BST();
    
    /*
     *  Find the maximum in a tree O(h)
     */
    Node* maximum(Node* n=nullptr) const;
    
    /*
     *  Find the minimum in a tree O(h)
     */
    Node* minimum(Node* n=nullptr) const;
    
    /*
     *  Find the successor of a node O(h)
     */
    Node* successor(Node* x) const;
    
    /*
     *  Find the predecessor of a node O(h)
     */
    Node* predecessor(Node* x) const;
    
    /*
     *  Find the node in the tree with a particular key O(h)
     */
    Node* search(const T& k) const;
    Node* search(const T& k, Node* x) const;
    
    /*
     *  Insert a key in the tree O(h)
     */
    void insert(T k);
    
    /*
     *  Delete a node in the tree O(h)
     */
    void remove(const T& k);
    void remove(Node* x);
    
    /*
     *  Print the tree on the stream f
     */
    void print(std::ostream& f=std::cout) const;
    
    /*
     *  In-order traversal O(n)
     */
    void printInOrder(Node* root, std::ostream& f=std::cout) const;
};

template<class T>
BST<T>::~BST() {
    // TODO
}

template<class T>
typename BST<T>::Node* BST<T>::maximum(Node* n) const {
    if(n==nullptr) n=root;
    Node* x=n;
    while(x->r!=nullptr) x=x->r;
    return x;
}

template<class T>
typename BST<T>::Node* BST<T>::minimum(Node* n) const {
    if(n==nullptr) n=root;
    Node* x=n;
    while(x->l!=nullptr) x=x->l;
    return x;
}

template<class T>
typename BST<T>::Node* BST<T>::successor(Node* x) const {
    if(x!=nullptr) {
        if(x->r!=nullptr) return minimum(x->r);
        else {
            // Father of x
            Node* y=x->f;
            
            // The successor of x is the first father
            // whose x is the left son
            while(y!=nullptr && x==y->r) {
                x=y;
                y=y->f;
            }
            
            // if x was a left leaf son,
            // its successor is its first
            // father, y
            return y;
        }
    }
    else return nullptr;
}

template<class T>
typename BST<T>::Node* BST<T>::predecessor(Node* x) const {
    if(x->l!=nullptr) return maximum(x->f);
    else {
        // Father of x
        Node* y=x->f;
        
        // The predecessor of x is the first father
        // whose x is the right son
        while(y!=nullptr && x==y->l) {
            x=y;
            y=y->f;
        }
        
        // if x was a right leaf son,
        // its successor is its first
        // father, y
        return y;
    }
}

template<class T>
typename BST<T>::Node* BST<T>::search(const T& k) const {
    return search(k, root);
}

template<class T>
typename BST<T>::Node* BST<T>::search(const T& k, Node* x) const {
    if(x==nullptr || x->key == k) return x;
    else {
        if(k <= x->key)
            return search(k, x->l);
        else
            return search(k, x->r);
    }
}

template<class T>
void BST<T>::insert(T k) {
    
    // Create the node
    Node* z = createNode(k);
    
    // Current node
    Node* x=root;
    
    // Store current node's father
    Node* y=nullptr;
    
    // Find the leaf where to insert
    while(x!=nullptr) {
        y=x;
        if(k <= x->key) x=x->l;
        else x=x->r;
    }
    
    // Set the father (last value of y)
    z->f=y;
    
    if(y==nullptr)
        // The tree was empty, so z is the root
        root=z;
    else if(k <= y->key)
        // z is left son
        y->l=z;
    else
        // z is right son
        y->r=z;

}

template<class T>
void BST<T>::remove(const T& k) {
    Node* x = search(k);
    remove(x);
}

template<class T>
void BST<T>::remove(Node* x) {
    if(x!=nullptr) {
        
        // 1st: the node hasn't son
        if(x->l==nullptr && x->r==nullptr) {
            if(x==x->f->l) x->f->l=nullptr;         // was left son
            else if(x==x->f->r) x->f->r=nullptr;    // was right son
            else root=nullptr;                      // was the root (BST with one node)
            delete x;
        }
        // 2nd: the node has one son (left or right)
        else if((x->l!=nullptr && x->r==nullptr) || (x->l==nullptr && x->r!=nullptr)) {
            
            // Find the son
            Node* son;
            if(x->l!=nullptr) son=x->l;
            else son=x->r;
            
            // Link son to father (s->f)
            son->f=x->f;
            
            // Link father to son (f->s)
            if(x->f!=nullptr) {
                if(x==x->f->l) x->f->l=son;
                else x->f->r=son;
            }
            else root=son;
            delete x;
        }
        // 3rd: the node has two sons
        else if(x->l!=nullptr && x->r!=nullptr) {
            
            // Find successor
            Node* s=successor(x);
            const T& sk=s->getKey();
            
            // Delete the successor
            remove(s);
            
            // Set x's key with its successor's key
            x->setKey(sk);
        }
        
    }
}

template<class T>
void BST<T>::print(std::ostream& f) const {
    printInOrder(root);
}

template<class T>
void BST<T>::printInOrder(Node* root, std::ostream& f) const {
    if(root!=nullptr) {
        printInOrder(root->l);
        f<<root->key<<std::endl;
        printInOrder(root->r);
    }
}


#endif /* BST_hpp */
