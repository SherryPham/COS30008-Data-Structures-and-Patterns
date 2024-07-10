
// COS30008, Tutorial 7, 2024

#pragma once

#include <iostream>
#include <functional>
#include <cassert>
#include <algorithm>

template<typename T>
using Cmp = std::function<bool(const T&, const T&)>;

template<typename T>
class BaseSorter
{
private:
    T* fCollection;
    size_t fSize;
    size_t fSwapCount;

public:
    BaseSorter(T* aCollection = nullptr, size_t aSize = 0) :
        fCollection(new T[aSize]),
        fSize(aSize),
        fSwapCount(0)
    {
        for (size_t i = 0; i < fSize; i++)
        {
            fCollection[i] = aCollection[i];
        }
    }

    virtual ~BaseSorter()
    {
        delete[] fCollection;
    }

    size_t size() const noexcept
    {
        return fSize;
    }

    size_t getSwapCount() const noexcept
    {
        return fSwapCount;
    }

    const T& operator[](size_t aIndex) const
    {
        assert(aIndex < fSize);

        return fCollection[aIndex];
    }

    void swap(size_t aLeftIndex, size_t aRightIndex)
    {
        assert(aLeftIndex < fSize && aRightIndex < fSize);

        std::swap(fCollection[aLeftIndex], fCollection[aRightIndex]);

        fSwapCount++;
    }

    virtual void operator()(bool aPrintStage = true, Cmp<T> aIsOutOfOrder = std::greater{}) noexcept
    {
        // intentionally empty
    }

    void printStage(size_t aIndent = 0) const noexcept
    {
        while (aIndent--)
        {
            std::cout << ' ';
        }

        std::cout << "[";

        if (fSize > 0)
        {
            for (size_t i = 0;; )
            {
                std::cout << fCollection[i++];

                if (i == fSize)
                {
                    break;
                }

                std::cout << ",";
            }
        }

        std::cout << "]" << std::endl;
    }
};
