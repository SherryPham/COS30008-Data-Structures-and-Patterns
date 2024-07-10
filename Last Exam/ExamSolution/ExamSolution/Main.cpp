
// COS30008, Final Exam, 2024

#include <iostream>
#include <string>

//#define P1
//#define P2
#define P3

size_t gCount = 0;

#ifdef P1

#include "List.h"

void runP1()
{
    gCount++;

    using CardinalList = List<size_t>;

    std::cout << "Test List Destructor:" << std::endl;

    CardinalList lList;

    for (size_t i = 1; i <= 1000; i++)
    {
        lList.push_back(i);
    }

    std::cout << "List with " << lList.size() << " elements goes out of scope." << std::endl;
}

#endif

#ifdef P2

#include "DynamicQueue.h"

void runP2()
{
    gCount++;
    
    DynamicQueue<int> lQueue;
    
    std::cout << "Enqueue elements:" << std::endl;

    for (int i = 1; i <= 30; i++)
    {
        lQueue.enqueue(i);
        std::cout << i << std::endl;
    }

    std::cout << "Dequeue elements:" << std::endl;

    std::optional<int> lValue = lQueue.top();

    while ( lValue )
    {
        std::cout << *lValue << std::endl;
        lQueue.dequeue();
        lValue = lQueue.top();
    }

    if ( lValue )
        std::cout << "failure" << std::endl;
    else
        std::cout << "success" << std::endl;
    
}

#endif

#ifdef P3

#include "PalindromeStringIterator.h"

void runP3()
{
    gCount++;

    // Palindrome by Scottish poet Alastair Reid
    std::string lTest =
        "T. Eliot, top bard, notes putrid tang emanating, is sad;\
         I'd assign it a name: gnat dirt upset on drab pot toilet.";

    std::cout << "Test palindrome iterators:" << std::endl;

    PalindromeStringIterator lIter(lTest);
    PalindromeStringIterator lForward = lIter.begin();
    PalindromeStringIterator lBackward = lIter.rbegin();

    while (lForward != lForward.end() && lBackward != lBackward.rend())
    {
        if (*lForward != *lBackward)
        {
            break;
        }
        
        ++lForward;
        lBackward--;
    }

    if (lForward == lForward.end() && lBackward == lBackward.rend())
    {
        std::cout << "String is a palindrome." << std::endl;
    }
    else
    {
        std::cout << "Oops. Something went wrong." << std::endl;
    }
}

#endif

int main()
{

#ifdef P1
    
    runP1();
    
#endif

#ifdef P2
    
    runP2();
    
#endif

#ifdef P3
    
    runP3();
    
#endif

    if (gCount)
    {
        std::cout << gCount << " test(s) completed." << std::endl;
    }
    else
    {
        std::cout << "No test enabled." << std::endl;
    }
    
    return 0;
}
