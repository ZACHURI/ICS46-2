// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
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
    void adding(Node*& current, const T& element);
    void destroyEverything(Node* current);
    void copyEverything(Node*& current, const Node* source);
    int height(Node* current);
    void rotateLeftOnce(Node*& current);
    void rotateLeftTwice(Node*& current);
    void rotateRightOnce(Node*& current);
    void rotateRightTwice(Node*& current);
};


template <typename T>
AVLSet<T>::AVLSet()
{
    root = nullptr;
}

template <typename T>
void AVLSet<T>::destroyEverything(Node* current)
{
    if(current == nullptr)
        return;
    destroyEverything(current->right);
    destroyEverything(current->left);
    delete current;
}

template <typename T>
AVLSet<T>::~AVLSet()
{
    destroyEverything(root);
}

template <typename T>
void AVLSet<T>::copyEverything(Node*& current, const Node* source)
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
AVLSet<T>::AVLSet(const AVLSet& s)
{
    copyEverything(root,s.root);
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
    :root{nullptr}
{
    std::swap(root,s.root);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
    std::swap(root,s.root);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}

template <typename T>
int AVLSet<T>::height(Node* current)
{
    int left,right;
    if(current == nullptr)
        return 0;
    left = height(current->left);
    right = height(current->right);
    if(left > right)
        return left + 1;
    else
        return right+1;
}

template <typename T>
void AVLSet<T>::rotateLeftOnce(Node*& current){
     Node* temp;

     temp = current->left;
     current->left = temp->right;
     temp->right = current;
     current = temp;
}

template <typename T>
void AVLSet<T>::rotateLeftTwice(Node*& current){
     rotateRightOnce(current->left);
     rotateLeftOnce(current);
}

template <typename T>
void AVLSet<T>::rotateRightOnce(Node*& current){
     Node* temp;

     temp = current->right;
     current->right = temp->left;
     temp->left = current;
     current = temp;
}

template <typename T>
void AVLSet<T>::rotateRightTwice(Node*& current){
     rotateLeftOnce(current->right);
     rotateRightOnce(current);
}

template <typename T>
void AVLSet<T>::adding(Node*& current,const T& element)
{
    if(current == nullptr)
        current = new Node{element};
    else if(element > current->value)
    {
        adding(current->right,element);
        if(height(current->right)-height(current->left) == 2)
        {
            if(element > current->right->value)
                rotateRightOnce(current);
            else
                rotateRightTwice(current);
        }
    }
    else if(element < current->value)
    {
        adding(current->left,element);
        if(height(current->left)-height(current->right) == 2)
        {
            if(element < current->left->value)
                rotateLeftOnce(current);
            else
                rotateLeftTwice(current);
        }
    }
}

template <typename T>
void AVLSet<T>::add(const T& element)
{
    adding(root,element);
}

template<typename T>
bool AVLSet<T>::isIn(const T& element, Node* current) const
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
        isIn(element,current->right);
    }
    else if(current != nullptr && element < current->value)
    {
        isIn(element,current->left);
    }
    return false;
   
}

template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return isIn(element,root);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return totalSize;
}



#endif // AVLSET_HPP

