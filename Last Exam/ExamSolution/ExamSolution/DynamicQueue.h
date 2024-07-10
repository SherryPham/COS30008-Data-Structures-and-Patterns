
// COS30008, Final Exam, 2024

#pragma once

#include <optional>
#include <cassert>

#include <iostream>

template<typename T>
class DynamicQueue
{
private:
    T* fElements;   
    size_t fFirstIndex; 
    size_t fLastIndex;  
    size_t fCurrentSize;

    
    // 2a) Create a new array with the new size
    void resize(size_t aNewSize)
    {
        T* newElements = new T[aNewSize];

        size_t currentQueueSize = fLastIndex - fFirstIndex;
        // Copy the existing elements from the old array to the new array
        std::copy(fElements + fFirstIndex, fElements + fLastIndex, newElements);


        delete[] fElements; // Delete the old array

        // Update the pointers and capacity
        fElements = newElements;
        fFirstIndex = 0;
        fLastIndex = currentQueueSize;
        fCurrentSize = aNewSize;
    }

    void ensure_capacity()
    {
        // 2b) If the queue is full, double the capacity
        if (fLastIndex == fCurrentSize)
        {
            resize(fCurrentSize == 0 ? 1 : fCurrentSize * 2);
        }
    }

    void adjust_capacity()
    {
        // 2c) If the size is less than 1/4 of the capacity, halve the capacity
        size_t currentQueueSize = fLastIndex - fFirstIndex;
        if (currentQueueSize < fCurrentSize / 4)
        {
            resize(fCurrentSize / 2);
        }
    }

public:

    // 2d) Constructor
    DynamicQueue() : fElements(nullptr), fFirstIndex(0), fLastIndex(0), fCurrentSize(0) {}

    // 2e) Destructor
    ~DynamicQueue()
    {
        delete[] fElements;
    }

    DynamicQueue(const DynamicQueue&) = delete;
    DynamicQueue& operator=(const DynamicQueue&) = delete;

    std::optional<T> top() const noexcept
    {
        // 2f) Return the first element if the queue is not empty
        if (fFirstIndex < fLastIndex)
        {
            return fElements[fFirstIndex];
        }
        return std::nullopt;
    }

    void enqueue(const T& aValue)
    {
        // 2g) Ensure capacity, then insert the element at the back
        ensure_capacity();
        fElements[fLastIndex++] = aValue;
    }

    void dequeue()
    {
        // 2h) Remove the element from the front
        if (fFirstIndex < fLastIndex)
        {
            fFirstIndex++;
            adjust_capacity();
        }
    }
};