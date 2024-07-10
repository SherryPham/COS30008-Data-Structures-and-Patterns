
// COS30008, Tutorial 7, 2024

#include <iostream>

#define P1
//#define P2
//#define P3

#ifdef P1

#include "BaseSorter.h"

void testP1()
{
    int lArray[] = { 45, 34, 8, 6, 4, 1, 0, -2, -3, -100 };
    const size_t lSize = sizeof(lArray) / sizeof(int);

    BaseSorter lSorter(lArray, lSize);

    std::cout << "Test BasicSorter:" << std::endl;

    lSorter.printStage();

    lSorter();

    lSorter.printStage();

    std::cout << "Number of swaps: " << lSorter.getSwapCount() << std::endl;

    std::cout << "Completed." << std::endl;
}

#endif

#ifdef P2

#include "BubbleSorter.h"

void testP2()
{
    int lArray[] = { 45, 34, 8, 6, 4, 1, 0, -2, -3, -100 };
    const size_t lSize = sizeof(lArray) / sizeof(int);

    BubbleSorter lSorter(lArray, lSize);

    std::cout << "Test BubbleSorter:" << std::endl;

    lSorter.printStage();

    lSorter();

    lSorter.printStage();

    std::cout << "Number of swaps: " << lSorter.getSwapCount() << std::endl;

    std::cout << "Completed." << std::endl;
}

#endif

#ifdef P3

#include "FisherAndYatesSorter.h"

void testP3()
{
    int lArray[] = { 45, 34, 8, 6, 4, 1, 0, -2, -3, -100 };
    const size_t lSize = sizeof(lArray) / sizeof(int);

    FisherAndYatesSorter lSorter(lArray, lSize);

    std::cout << "Test FisherAndYatesSorter:" << std::endl;

    lSorter.printStage();

    lSorter(false);

    lSorter.printStage();

    std::cout << "Number of swaps: " << lSorter.getSwapCount() << std::endl;

    std::cout << "Completed." << std::endl;
}

#endif

int main()
{
#ifdef P1

    testP1();

#endif

#ifdef P2

    testP2();

#endif

#ifdef P3

    testP3();

#endif

    return 0;
}
