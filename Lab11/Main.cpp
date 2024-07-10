
// COS30008, Tutorial 11, 2024

#include <iostream>
#include <string>

#define P1
//#define P2

#ifdef P1

#include "DoublyLinkedList.h"

void testP1()
{
    std::cout << "Test DoublyLinkedList:" << std::endl;
    
    using StringList = DoublyLinkedList<std::string>;
    using ListNode = StringList::Node;

    std::string lA( "AAAA" );
    std::string lD( "DDDD" );
    std::string lF( "FFFF" );
    StringList lNodeC( "CCCC" );
    StringList lNodeD( lD );

    ListNode One = StringList::makeNode( lA );
    ListNode Two = StringList::makeNode( "BBBB" );
    ListNode Three = StringList::makeNode( lNodeC );
    ListNode Four = StringList::makeNode( lNodeD );
    ListNode Five = StringList::makeNode( StringList( "EEEE" ) );
    ListNode Six = StringList::makeNode( StringList( lF ) );

    // link nodes
    One->fNext = Two;
    One->fPrevious = Six;
    Two->fNext = Three;
    Two->fPrevious = One;
    Three->fNext = Four;
    Three->fPrevious = Two;
    Four->fNext = Five;
    Four->fPrevious = Three;
    Five->fNext = Six;
    Five->fPrevious = Four;
    Six->fNext = One;
    Six->fPrevious = Five;
    
    std::cout << "Traverse links in forward direction:" << std::endl;
    
    ListNode lForward = Four;

    do
    {
        std::cout << "Value: " << lForward->fData << std::endl;
        lForward = lForward->fNext;
    } while ( lForward != Four );

    std::cout << "Traverse links in backwards direction:" << std::endl;

    ListNode lBackwards = Four;

    do
    {
        std::cout << "Value: " << lBackwards->fData << std::endl;
        lBackwards = lBackwards->fPrevious.lock();
    } while ( lBackwards != Four );

    std::cout << "Traverse links in forward direction (Four <==> Six):" << std::endl;

    Four->swap( *Six );
    
    ListNode lForward2 = Four;

    do
    {
        std::cout << "Value: " << lForward2->fData << std::endl;
        lForward2 = lForward2->fNext;
    } while ( lForward2 != Four );

    std::cout << "Traverse links in forward direction (isolate Three):" << std::endl;

    Three->isolate();
    
    ListNode lForward3 = Four;

    do
    {
        std::cout << "Value: " << lForward3->fData << std::endl;
        lForward3 = lForward3->fNext;
    } while ( lForward3 != Four );
    
    std::cout << "Test complete." << std::endl;
}

#endif

#ifdef P2

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

void testP2()
{
    std::cout << "Test DoublyLinkedListIterator:" << std::endl;

    using StringList = DoublyLinkedList<std::string>;
    using ListNode = StringList::Node;

    std::string lA( "AAAA" );
    std::string lD( "DDDD" );
    std::string lF( "FFFF" );
    StringList lNodeC( "CCCC" );
    StringList lNodeD( lD );

    ListNode One = StringList::makeNode( lA );
    ListNode Two = StringList::makeNode( "BBBB" );
    ListNode Three = StringList::makeNode( lNodeC );
    ListNode Four = StringList::makeNode( lNodeD );
    ListNode Five = StringList::makeNode( StringList( "EEEE" ) );
    ListNode Six = StringList::makeNode( StringList( lF ) );

    // link nodes
    One->fNext = Two;       // no previous link
    Two->fNext = Three;
    Two->fPrevious = One;
    Three->fNext = Four;
    Three->fPrevious = Two;
    Four->fNext = Five;
    Four->fPrevious = Three;
    Five->fNext = Six;
    Five->fPrevious = Four;
    Six->fPrevious = Five;  // no next link

    using Iterator = DoublyLinkedListIterator<std::string>;
 
    Iterator lIter( One, Six );
    
    std::cout << "Forward iteration:" << std::endl;
    
    for ( auto& item : lIter )
    {
        std::cout << item << std::endl;
    }
    
    std::cout << "Backwards iteration:" << std::endl;
    
    for ( auto iter = lIter.rbegin(); iter != iter.rend(); iter-- )
    {
        std::cout << *iter << std::endl;
    }
    
    std::cout << "Test complete." << std::endl;
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
    
#ifndef P1
    
    #ifndef P2
    
    std::cout << "No test enabled." << std::endl;
    
    #endif
    
#endif
    
    return 0;
}
