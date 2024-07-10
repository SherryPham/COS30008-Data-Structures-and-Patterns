
// COS30008, Final Exam, 2024

#pragma once

#include <memory>
#include <algorithm>
#include <iostream>

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
    static Node makeNode( Args&&... args )
    {
        // make_share<T, Args...>
        return std::make_shared<DoublyLinkedList>( std::forward<Args>(args)...  );
    }
    
    DoublyLinkedList( const T& aData ) noexcept :
        fData(aData),
        fNext(),
        fPrevious()
    {}
    
    DoublyLinkedList( T&& aData ) noexcept :
        fData(std::move(aData)),
        fNext(),
        fPrevious()
    {}

    ~DoublyLinkedList() noexcept
    {
        std::cout << "Node [" << fData << "] destroyed." << std::endl;
    }
    
    void isolate() noexcept
    {
        if ( fNext )
        {
            fNext->fPrevious = fPrevious;
        }

        Node lNode = fPrevious.lock();

        if ( lNode )
        {
            lNode->fNext = fNext;
        }
        
        fPrevious.reset();
        fNext.reset();
    }

    void swap( DoublyLinkedList& aOther ) noexcept
    {
        std::swap( fData, aOther.fData );
    }
};
