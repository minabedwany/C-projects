// HashSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include <iostream>

template <typename ElementType>
struct hNode
{
    hNode<ElementType> * next = nullptr;
    ElementType value;

    hNode()
    {
        next = nullptr;
    }

    hNode(ElementType info)
    {
        next = nullptr;
        value = info;
    }

    hNode(ElementType info, hNode<ElementType> * tempnext)
    {
        next = tempnext;
        value = info;
    }
};



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet() noexcept;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;
    int mySize = 0;
    int myCapacity = DEFAULT_CAPACITY;
    hNode<ElementType> * ptr = nullptr;
    hNode<ElementType> ** hashArray = nullptr;

    void removeNodes(hNode<ElementType> * node)
    {
        if(node->next != nullptr)
            removeNodes(node->next);
        delete node;
    }

    void deleteArray()
    {
        if(hashArray != nullptr)
        {
            for(int i = 0; i < myCapacity; ++i)
            {
                if(hashArray[i] != nullptr)
                    removeNodes(hashArray[i]);
            }
            delete[] hashArray;
        } 
    }
       
    void copy(hNode<ElementType> ** array, int cap)
    {
        hNode<ElementType> * temp = nullptr;
        hNode<ElementType> ** newHList = new hNode<ElementType>*[cap];    
    
        for(int i = 0; i<cap; ++i)
            newHList[i] = nullptr;

        for(int i = 0; i<cap; ++i)
        {
            if(array[i] != nullptr)
            {
                ptr = array[i];
                while(ptr != nullptr)
                {
                    int num = hashFunction(ptr->value) % cap;
                    
                    if(newHList[num] == nullptr)
                    {
                        newHList[num] = new hNode<ElementType>(ptr->value);
                        ptr = ptr->next;
                    }
                    else
                    {
                        temp = newHList[num];
                        newHList[num] = new hNode<ElementType>(ptr->value, temp);
                        ptr = ptr->next;
                    }
                }
            }
        }
        deleteArray();
        hashArray = newHList;
        myCapacity = cap;
        temp = nullptr;

    } 

    void resize()
    {
        int doublecap = 2*myCapacity;
        hNode<ElementType> * temp = nullptr;
        hNode<ElementType> ** newHList = new hNode<ElementType>*[doublecap];

        for(int i = 0; i<myCapacity; ++i)
            newHList[i] = nullptr;

        for(int i = 0; i<myCapacity; ++i)
        {
            if(hashArray[i] != nullptr)
            {
                ptr = hashArray[i];
                while(ptr != nullptr)
                {
                    int num = hashFunction(ptr->value) % doublecap;

                    if(newHList[num] == nullptr)
                    {
                        newHList[num] = new hNode<ElementType>(ptr->value);
                        ptr = ptr->next;
                    }
                    else
                    {
                        temp = newHList[num];
                        newHList[num] = new hNode<ElementType>(ptr->value, temp);
                        ptr = ptr->next;
                    }
                }
            }
        }
        deleteArray();
        hashArray = newHList;
        myCapacity = doublecap;
        temp = nullptr;

    }
    
};


namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    hashArray = new hNode<ElementType>*[myCapacity];
    for(int i = 0; i<myCapacity; ++i)
        hashArray[i] = nullptr; 
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    deleteArray();
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    copy(s.hashArray, s.myCapacity);
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    hashArray = s.hashArray;
    myCapacity = s.myCapacity;
    mySize = s.mySize;
    hashFunction = s.hashFunction;
    ptr = s.ptr;

    s.hashArray = nullptr;
    s.myCapacity = 0;
    s.mySize = 0;
    s.ptr = nullptr;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    hashFunction = s.hashFunction;
    copy(s.hashArray, s.myCapacity);
     
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    hNode<ElementType> ** tempArray = hashArray;
    hNode<ElementType> * tempPtr = ptr;
    int tempSize = mySize;
    int tempCap = myCapacity;
    HashFunction tempHash = hashFunction;

    hashArray = s.hashArray;
    myCapacity = s.myCapacity;
    mySize = s.mySize;
    hashFunction = s.hashFunction;
    ptr = s.ptr;

    s.hashArray = tempArray;
    s.myCapacity = tempCap;
    s.mySize = tempSize;
    s.ptr = tempPtr;
    s.hashFunction = tempHash;

    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    double ratio = double(mySize)/double(myCapacity);
   
    if(ratio > 0.8)
        resize();

    int num = hashFunction(element) % myCapacity;
    if(hashArray[num] == nullptr)
    {
        hashArray[num] = new hNode<ElementType>{element};
        ++mySize;
    }
    else
    {
        ptr = hashArray[num];
        hashArray[num] = new hNode<ElementType>{element, ptr};
        ++mySize;
    }
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    int num = hashFunction(element) % myCapacity;
    if(hashArray[num] == nullptr)
        return false;
    else
    {
        hNode<ElementType> * temp = hashArray[num];
        while(temp != nullptr)
        {
            if(temp->value == element)
                return true;
            temp = temp->next;
        }
    return false;
    }
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return mySize;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    int counter = 0;
    if(index < 0 && index >= myCapacity)
        return 0;
    if(hashArray[index] == nullptr)
        return 0;
    else
    {
        hNode<ElementType> * temp = hashArray[index];
        while(temp != nullptr)
        {
            temp = temp->next;
            ++counter;
        }
    } 
    return counter;
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if(index < 0 && index >= myCapacity)
        return false;
    if(hashArray[index] == nullptr)
        return false;
    else
    {
        hNode<ElementType> * temp = hashArray[index];
        while(temp != nullptr)
        {
            if(temp->value == element)
                return true;
            temp = temp->next;
        }
    return false;
    }
}



#endif // HASHSET_HPP

