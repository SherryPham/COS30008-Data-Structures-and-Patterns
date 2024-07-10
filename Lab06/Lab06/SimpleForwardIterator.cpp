
// COS30008, Tutorial 6, 2024

#include "SimpleForwardIterator.h"

#include <cassert>

SimpleForwardIterator::SimpleForwardIterator(const DataWrapper* aCollection) noexcept :
    fCollection(aCollection),
    fIndex(0)
{
    assert(fCollection != nullptr);
}

const DataMap& SimpleForwardIterator::operator*() noexcept
{
    return (*fCollection)[fIndex];
}

SimpleForwardIterator& SimpleForwardIterator::operator++() noexcept
{
    fIndex++;

    return *this;
}

SimpleForwardIterator SimpleForwardIterator::operator++(int) noexcept
{
    SimpleForwardIterator old = *this;

    ++(*this);

    return old;
}

bool SimpleForwardIterator::operator==(const SimpleForwardIterator& aOther) const noexcept
{
    return fCollection == aOther.fCollection && fIndex == aOther.fIndex;
}

bool SimpleForwardIterator::operator!=(const SimpleForwardIterator& aOther) const noexcept
{
    return !(*this == aOther);
}

SimpleForwardIterator SimpleForwardIterator::begin() const noexcept
{
    SimpleForwardIterator copy = *this;

    copy.fIndex = 0;

    return copy;
}

SimpleForwardIterator SimpleForwardIterator::end() const noexcept
{
    SimpleForwardIterator copy = *this;

    copy.fIndex = fCollection->size();

    return copy;
}
