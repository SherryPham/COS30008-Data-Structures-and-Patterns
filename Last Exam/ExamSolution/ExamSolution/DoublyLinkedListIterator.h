
// COS30008, Final Exam, 2024

#pragma once

#include <cassert>

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
public:
    using Iterator = DoublyLinkedListIterator<T>;
    using Node = typename DoublyLinkedList<T>::Node;

    enum class States
    {
        BEFORE,
        DATA,
        AFTER
    };
    
    DoublyLinkedListIterator( const Node& aHead, const Node& aTail ) noexcept :
        fHead(aHead),
        fTail(aTail),
        fCurrent(aHead),
        fState(States::DATA)
    {
        // sound head and tail hooks
        assert( !fHead == !fTail );
        
        if ( !fHead )
        {
            fState = States::AFTER;
        }
    }
    
    const T& operator*() const noexcept
    {
        return fCurrent->fData;
    }
    
    Iterator& operator++() noexcept     // prefix
    {
        switch ( fState )
        {
            case States::BEFORE:
                fCurrent = fHead;
                
                if ( fCurrent )
                {
                    fState = States::DATA;
                }
                else
                {
                    fState = States::AFTER;
                }
                
                break;
                
            case States::DATA:
                fCurrent = fCurrent->fNext;

                if ( !fCurrent )
                {
                    fState = States::AFTER;
                }

                break;
            
            case States::AFTER:
                break;
        }
        
        return *this;
    }
    
    Iterator operator++(int) noexcept // postfix
    {
        Iterator old = *this;
        
        ++(*this);
        
        return old;
    }
    
    Iterator& operator--() noexcept     // prefix
    {
        switch ( fState )
        {
            case States::BEFORE:

                break;
                
            case States::DATA:
                fCurrent = fCurrent->fPrevious.lock();

                if ( !fCurrent )
                {
                    fState = States::BEFORE;
                }

                break;
            
            case States::AFTER:
                fCurrent = fTail;
                
                if ( fCurrent )
                {
                    fState = States::DATA;
                }
                else
                {
                    fState = States::BEFORE;
                }
                
                break;
        }
        
        return *this;
    }
    
    Iterator operator--(int) noexcept // postfix
    {
        Iterator old = *this;
        
        --(*this);
        
        return old;
    }

    bool operator==( const Iterator& aOther ) const noexcept
    {
        return
            fHead == aOther.fHead &&
            fTail == aOther.fTail &&
            fState == aOther.fState &&
            fCurrent == aOther.fCurrent;
    }
    
    bool operator!=( const Iterator& aOther ) const noexcept
    {
        return !(*this == aOther);
    }
    
    Iterator begin() const noexcept
    {
        return ++(rend());
    }
    
    Iterator end() const noexcept
    {
        Iterator iter = *this;
        
        iter.fCurrent = nullptr;
        iter.fState = States::AFTER;
        
        return iter;
    }
    
    Iterator rbegin() const noexcept
    {
        return --(end());
    }
    
    Iterator rend() const noexcept
    {
        Iterator iter = *this;
        
        iter.fCurrent = nullptr;
        iter.fState = States::BEFORE;
        
        return iter;
    }

private:
    Node fHead;
    Node fTail;
    Node fCurrent;
    States fState;
};
