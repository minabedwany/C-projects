// AVLSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"
#include <iostream>

template <typename ElementType>
struct tNode
{
    tNode<ElementType> * right = nullptr;
    tNode<ElementType> * left = nullptr;
    ElementType value;
    int height = 0;

};

template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet() noexcept;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    int mySize = 0;
    bool balance = false;
    tNode<ElementType> * root = nullptr;

    void clearTree(tNode<ElementType> * node)
    {
        if(node != nullptr)
        {
            clearTree(node->right);
            clearTree(node->left);
            delete node;
        }
    }
        
    tNode<ElementType>* copy(tNode<ElementType> * src, tNode<ElementType> * dest)
    {
        if(src == nullptr)
        {
            dest = nullptr;
            return dest;
        }
        else
        {
            dest = new tNode<ElementType>;
            dest->value = src->value;
            dest->left = nullptr;
            dest->right = nullptr;
            ++mySize;
            dest->right = copy(src->right, dest->right);
            dest->left = copy(src->left, dest->left);
        }
    return dest;
    }
    
    int balanceChecker(tNode<ElementType> * node)
    {
        if(node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    tNode<ElementType>* rr(tNode<ElementType> * node)
    {
        tNode<ElementType> *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    tNode<ElementType>* ll(tNode<ElementType> * node)
    {
        tNode<ElementType> *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }
    
    tNode<ElementType>* lr(tNode<ElementType> * node)
    {
        tNode<ElementType> *temp = node->left;
        node->left = rr(temp);
        return ll(node);
    }

    tNode<ElementType>* rl(tNode<ElementType> * node)
    {
        tNode<ElementType> *temp = node->right;
        node->right = ll(temp);
        return rr(node);
    }

    int max(int x, int y)
    {
        if(x > y)
            return x;
        else
            return y;
    }

    tNode<ElementType>* balancer(tNode<ElementType>* node)
    {
        if(balance)
        {
            int num = balanceChecker(node);
            if(num > 1)
            {
                if(balanceChecker(node->left) > 0)
                    node = ll(node);
                else
                    node = lr(node);
            }
            if(num < -1)
            {
                if(balanceChecker(node->right) > 0)
                    node = rl(node);
                else
                    node = rr(node);
            }
        }
        return node;
    }

    tNode<ElementType> * insert(tNode<ElementType> * node, const ElementType& element)
    {
        if(node == nullptr)
        {
            node = new tNode<ElementType>;
            node->value = element;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
            ++mySize;
            return node;
        }
       
        if(node->value == element)
            return node;

        if(node->value > element)
            node->left = insert(node->left, element);
            node = balancer(node);
        if(node->value < element)
            node->right = insert(node->right, element);
            node = balancer(node);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    bool search(tNode<ElementType> * node, const ElementType& element) const
    {
        if(node == nullptr)
            return false;
        if(node->value == element)
            return true;
        if(node->value > element)
            return search(node->left, element);
        else
            return search(node->right, element);
    }

    int getHeight(tNode<ElementType> * node) const
    {
        if(node == nullptr)
            return 0;
        return node->height;
        
    }

    void pre(VisitFunction visitt, tNode<ElementType>* node) const
    {
        if(node == nullptr)
            return;
        visitt(node->value);
        pre(visitt, node->left);
        pre(visitt, node->right);
    }

    void in(VisitFunction visitt, tNode<ElementType>* node) const
    {
        if(node == nullptr)
            return;
        in(visitt, node->left);
        visitt(node->value);
        in(visitt, node->right);
    }

    void post(VisitFunction visitt, tNode<ElementType>* node) const
    {
        if(node == nullptr)
            return;
        post(visitt, node->left);
        post(visitt, node->right);
        visitt(node->value);
    }
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    balance = shouldBalance;
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    clearTree(root);
    mySize = 0;
    root = nullptr;
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    root = copy(s.root, root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    root = s.root;
    mySize = s.mySize;

    s.root = nullptr;
    mySize= 0;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    clearTree(root);
    root = copy(s.root, root);
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    tNode<ElementType> * temproot = root;
    int tempsize = mySize;

    root = s.root;
    mySize = s.mySize;

    s.root = temproot;
    mySize= tempsize;
    
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
   
    root = insert(root, element);
}

template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    return search(root, element);
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return mySize;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const
{
   if(root == nullptr)
        return -1;
   if(balance)
        return getHeight(root) - 1;
   return getHeight(root);
   
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    pre(visit, root);
}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    in(visit, root);
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    post(visit, root);
}



#endif // AVLSET_HPP

