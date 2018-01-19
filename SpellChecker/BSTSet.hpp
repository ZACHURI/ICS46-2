// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
   
    int totalSize = 0;
    struct Node
    {
        T value;
        Node* left;
        Node* right;
    };
    Node* root;
    Node* current;
    bool isIn(const T& element, Node* current) const;
    void adding(const T& element,Node*& current);
    void destroyEverything(Node* current);
    void copyEverything(Node*& current, const Node* source);
};


template <typename T>
BSTSet<T>::BSTSet()
{ 
    root = nullptr;
    //current = root;
}

template <typename T>
void BSTSet<T>::destroyEverything(Node* current)
{
    if(current == nullptr)
        return;
    destroyEverything(current->right);
    destroyEverything(current->left);
    delete current;
}

template <typename T>
BSTSet<T>::~BSTSet()
{
    destroyEverything(root);
}

template <typename T>
void BSTSet<T>::copyEverything(Node*& current, const Node* source)
{
    if(source == nullptr)
        current = nullptr;
    else
    {
        current = new Node{source->value};
        if(current->right == nullptr && current->left == nullptr)
            return;
        copyEverything(current->left,source->left);
        copyEverything(current->right,source->right);
    }
}

template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    copyEverything(root,s.root);
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
    :root{nullptr}
{
    std::swap(root,s.root);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if(this != &s)
    {
        destroyEverything(this->root);
        root = nullptr;
        copyEverything(root,s.root);

    }
    return *this;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
    std::swap(root,s.root);
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}

template<typename T>
bool BSTSet<T>::isIn(const T& element, Node* current) const
{
    if(current !=nullptr && element == current->value)
    {
        return true;
    }
    else if(current == nullptr)
    {
        return false;
    }
    else if(current != nullptr && element > current->value)
    {
        return isIn(element,current->right);
    }
    else if(current != nullptr && element < current->value)
    {
        return isIn(element,current->left);
    }
    return false;
}

template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    
    return isIn(element,root);
}

template <typename T>
void BSTSet<T>::adding(const T& element,Node*& current)
{
    if(current == nullptr)
    {
        current = new Node{element,nullptr,nullptr};
        totalSize++;
    }
    else if(element > current->value)
    {
        current = current->right;
        adding(element,current);
    }
    else if(element < current->value)
    {
        current = current->left;
        adding(element,current);
    }
    else if(element == current->value)
        return;
}

template <typename T>
void BSTSet<T>::add(const T& element)
{
    adding(element,root);
}

template <typename T>
unsigned int BSTSet<T>::size() const
{
    return totalSize;
}



#endif // BSTSET_HPP

