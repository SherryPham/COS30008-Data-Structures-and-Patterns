
// COS30008, Final Exam, 2024

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class List
{
private:
    using Node = typename DoublyLinkedList<T>::Node;
    
    Node fHead;
    Node fTail;
    size_t fSize;
    
public:

    using Iterator = DoublyLinkedListIterator<T>;
    
    List() noexcept :
        fSize(0)
    {}

    // Problem 1
    ~List() noexcept
    {
        Node lCurrent = fTail;  // Keep a temporary pointer to traverse from tail to head
        fTail.reset();   // Reset the tail pointer

        // Traverse the list from tail to head, deallocating nodes
        while (lCurrent)
        {
            Node lPrevious = lCurrent->fPrevious.lock();    
            lCurrent->fPrevious.reset();
            lCurrent->fNext.reset();
            lCurrent = lPrevious;
        }

        fHead.reset();
      
        //while (fTail) 
        //{
        //    auto lNext = fFail->fPrevious; //store next node
        //    fTail.reset();  //delete current head
        //    fTail = lPrevious;  //move to next node 
        //}
    }
    
    List( const List& aOther ) :
        List()
    {
        for ( auto& item : aOther )
        {
            push_back( item );
        }
    }
    
    List& operator=( const List& aOther )
    {
        if ( this != &aOther )
        {
            this->~List();
            
            new (this) List( aOther );
        }
        
        return *this;
    }
    
    List( List&& aOther ) noexcept :
        List()
    {
        swap( aOther );
    }
    
    List& operator=( List&& aOther ) noexcept
    {
        if ( this != &aOther )
        {
            swap( aOther );
        }
        
        return *this;
    }

    void swap( List& aOther ) noexcept
    {
        std::swap( fHead, aOther.fHead );
        std::swap( fTail, aOther.fTail );
        std::swap( fSize, aOther.fSize );
    }
    
    size_t size() const noexcept
    {
        return fSize;
    }
    
    template<typename U>
    void push_front( U&& aData )
    {
        Node lNode = DoublyLinkedList<T>::makeNode( std::forward<U>(aData) );

        if ( !fHead )                               // first element
        {
            fTail = lNode;                          // set tail to first element
        }
        else
        {
            lNode->fNext = fHead;                   // new node becomes head
            fHead->fPrevious = lNode;               // new node previous of head
        }
        
        fHead = lNode;                              // new head
        fSize++;                                    // increment size
    }
    
    template<typename U>
    void push_back( U&& aData )
    {
        Node lNode = DoublyLinkedList<T>::makeNode( std::forward<U>(aData) );

        if ( !fTail )                               // first element
        {
            fHead = lNode;                          // set head to first element
        }
        else
        {
            lNode->fPrevious = fTail;               // new node becomes tail
            fTail->fNext = lNode;                   // new node next of tail
        }
        
        fTail = lNode;                              // new tail
        fSize++;                                    // increment size
    }
    
    void remove( const T& aElement ) noexcept
    {
        Node lNode = fHead;                         // start at first
        
        while ( lNode )                             // Are there still nodes available?
        {
            if ( lNode->fData == aElement )         // Have we found the node?
            {
                break;                              // stop the search
            }

            lNode = lNode->fNext;                   // move to next node
        }
        
        if ( lNode )                                // We have found a first matching node.
        {
            if ( fHead == lNode )                   // remove head
            {
                fHead = lNode->fNext;               // make lNode's next head
            }

            if ( fTail == lNode )                   // remove tail
            {
                fTail = lNode->fPrevious.lock();    // make lNode's previuos tail, requires std::shared_ptr
            }
            
            lNode->isolate();                       // isolate node, automatically freed
            fSize--;                                // decrement count
        }
    }
    
    const T& operator[]( size_t aIndex ) const
    {
        assert( aIndex < fSize );

        Node lNode = fHead;

        while ( aIndex-- )
        {
            lNode = lNode->fNext;
        }

        return lNode->fData;
    }
    
    Iterator begin() const noexcept
    {
        return Iterator( fHead, fTail );
    }

    Iterator end() const noexcept
    {
        return begin().end();
    }

    Iterator rbegin() const noexcept
    {
        return begin().rbegin();
    }

    Iterator rend() const noexcept
    {
        return begin().rend();
    }
};
