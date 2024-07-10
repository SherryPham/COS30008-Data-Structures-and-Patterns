
// COS30008, Tutorial 6, 2024

#pragma once

#include "DataWrapper.h"

class OrderingForwardIterator
{
private:
    const DataWrapper* fCollection;
    size_t fIndex;
    size_t fMapPosition;
    
    void setMapPosition();

public:
    
    OrderingForwardIterator( const DataWrapper* aCollection ) noexcept;
    
    const DataMap& operator*() noexcept;
    
    OrderingForwardIterator& operator++() noexcept;     // prefix
    OrderingForwardIterator operator++(int) noexcept;   // postfix

    bool operator==( const OrderingForwardIterator& aOther ) const noexcept;
    bool operator!=( const OrderingForwardIterator& aOther ) const noexcept;
    
    OrderingForwardIterator begin() const noexcept;
    OrderingForwardIterator end() const noexcept;
};
