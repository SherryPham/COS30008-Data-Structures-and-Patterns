
// COS30008, Tutorial 6, 2024

#pragma once

#include "DataWrapper.h"

class SimpleForwardIterator
{
private:
    const DataWrapper* fCollection;
    size_t fIndex;

public:
    
    SimpleForwardIterator( const DataWrapper* aCollection ) noexcept;
    
    const DataMap& operator*() noexcept;
    
    SimpleForwardIterator& operator++() noexcept;       // prefix
    SimpleForwardIterator operator++(int) noexcept;     // posfix

    bool operator==( const SimpleForwardIterator& aOther ) const noexcept;
    bool operator!=( const SimpleForwardIterator& aOther ) const noexcept;
    
    SimpleForwardIterator begin() const noexcept;
    SimpleForwardIterator end() const noexcept;
};
