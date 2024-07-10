
// COS30008, Tutorial 7, 2024

#pragma once

#include "BaseSorter.h"

#include <cstdlib>
#include <ctime>

template<typename T>
class FisherAndYatesSorter : public BaseSorter<T>
{
private:

    void shuffle() noexcept
    {
        size_t n = this->size();

        while (n > 0)
        {
            size_t k = std::rand() % n;

            n--;

            this->swap(n, k);
        }
    }

    bool isSorted(Cmp<T> aIsOutOfOrder) const noexcept
    {
        for (size_t i = 1; i < this->size(); i++)
        {
            if (aIsOutOfOrder((*this)[i - 1], (*this)[i]))
            {
                return false;
            }
        }

        return true;
    }

public:

    FisherAndYatesSorter(T* aCollection = nullptr, size_t aSize = 0) :
        BaseSorter<T>(aCollection, aSize)
    {
        std::srand(static_cast<unsigned>(std::time(NULL)));
    }

    virtual void operator()(bool aPrintStage = true, Cmp<T> aIsOutOfOrder = std::greater{}) noexcept override
    {
        bool lSorted = false;

        do
        {
            lSorted = this->isSorted(aIsOutOfOrder);

            if (aPrintStage)
            {
                this->printStage(2);
            }

            if (!lSorted)
            {
                this->shuffle();
            }

        } while (!lSorted);
    }
};
