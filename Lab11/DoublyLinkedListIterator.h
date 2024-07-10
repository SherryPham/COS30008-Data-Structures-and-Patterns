
// COS30008, Tutorial 11, 2024

#pragma once

#include <cassert>
#include <stdexcept>

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
    
    DoublyLinkedListIterator(const Node& aHead, const Node& aTail) noexcept :
        fHead(aHead),
        fTail(aTail),
        fCurrent(aHead),            // set the position at the list element
        fState(States::DATA)        // set the States
    {
        assert(!fHead == !fTail);
        if (!fHead)
        {
            fState = States::AFTER;
        }
    }

    const T& operator*() const noexcept
    {
        return fCurrent->fData;     // have to return the payload (fData) from the position (fCurrent)
    }
    
    Iterator& operator++() noexcept		    // prefix
    {
        switch (fState)
        {
            case States::BEFORE: 
            fCurrent = fHead;
            
            if (fCurrent)
            {
            fState = States::DATA;
            }

            else
            {
                State = States::AFTER;
            }
            break;

            
            
            case States::DATA:
                fCurrent = fCurrent->fNext;

            if (!fCurrent)
            {
                fState = States::AFTER;
            }
            break;

           
            case States::AFTER:
                break;
       
        }
        return *this;
    }
    Iterator operator++(int) noexcept		// postfix
    {
        iterator old = *this;
        ++(*this);
        return old;
    }
    
    Iterator& operator--() noexcept 		// prefix
    {
        switch (fState)
        {
        case States::BEFORE:
            fCurrent = fHead;

            if (fCurrent)
            {
                fState = States::DATA;
            }

            else
            {
                State = States::AFTER;
            }
            break;



        case States::DATA:
            fCurrent = fCurrent->fNext;

            if (!fCurrent)
            {
                fState = States::AFTER;
            }
            break;


        case States::AFTER:
            break;

        }
        return *this;
    }

    Iterator operator--(int) noexcept		// postfix
    {
        iterator old = *this;
        --(*this);
        return old;
    }

    bool operator==(const Iterator& aOther) const noexcept
    {
        // head == head, tail == tail, current == current, state == state
        return fHead == aOther.fHead && fTail == aOther.fTail && fCurrent == aOther.fCurrent state == state
    }

    bool operator!=(const Iterator& aOther) const noexcept
    {
        return (*this == aOther.);
    }
    
    Iterator begin() const noexcept
    {
        return ++(rend());
    }
    Iterator end() const noexcept
    {
        Iterator iter = *this;
        iter.fCurrent = nullptr;    // alocate to empty handler
        iter.fState = States::AFTER;
    }
    Iterator rbegin() const noexcept
    {
        return --(rend());
    }
    Iterator rend() const noexcept
    {
        Iterator iter = *this;
        iter.fCurrent = nullptr;    // alocate to empty handler
        iter.fState = States::BEFORE;
    }

private:
    Node fHead;
    Node fTail;
    Node fCurrent;
    States fState;
};
