
// COS30008, Tutorial 11, 2024
// Tran Anh Thu Pham
// DoublyLinkedlist.h

#pragma once

#include <memory>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:

    using Node = std::shared_ptr<DoublyLinkedList<T>>;
    using Next = std::shared_ptr<DoublyLinkedList<T>>;
    using Previous = std::weak_ptr<DoublyLinkedList<T>>;

    T fData;
    Node fNext;
    Previous fPrevious;

    // factory method for list nodes
    template<typename... Args>
    static Node makeNode(Args&&... args)  // factory method 'makeNode'
    {
        // use perfect forwarding std::forward
        return std::make_shared<DoublyLinkedList>(std::forward<Args&&>(args)...);
    }
    
    // L value
    DoublyLinkedList( const T& aData ) noexcept : 
        fData(aData),
        fNext(),        // class type = shared pointer of doublyLinkedList node
        fPrevious()     // class type = shared pointer of doublyLinkedList node
    {} 

    //R value
    DoublyLinkedList( T&& aData ) noexcept :
        fData(std::move(aData)),    // movable object in R value
        fNext(),        
        fPrevious()
    {}

    void isolate() noexcept
    {
        if (fNext)
        {
            fNext->fPrevious = fPrevious;
        }

        Node lNode = fPrevious.lock();

        if (lNode)
        {
            lNode->fNext = fNext;
        }
        fPrevious.reset();
        fNext.reset();
    }

    void swap(DoublyLinkedList& aOther) noexcept        // want to change the payload
    {
        // change the pay load with something
        // to ensure the 'move' of payload
        std::swap(fData, aOther.fData);
    }
};
