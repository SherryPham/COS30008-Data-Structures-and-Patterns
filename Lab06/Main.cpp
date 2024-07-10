
// COS30008, Tutorial 6, 2024

#include <iostream>

#include "DataWrapper.h"

//#define P1
//#define P2

#ifdef P1

#include "SimpleForwardIterator.h"

void testP1( const DataWrapper& aWrapper )
{
    for ( const auto& item : SimpleForwardIterator( &aWrapper) )
    {
        std::cout << static_cast<char>(item);
    }

    std::cout << std::endl;
}

#endif
    
#ifdef P2

#include "OrderingForwardIterator.h"

void testP2( const DataWrapper& aWrapper )
{
    for ( const auto& item : OrderingForwardIterator( &aWrapper) )
    {
        std::cout << static_cast<char>(item);
    }

    std::cout << std::endl;
}

#endif


int main( int argc, char* argv[] )
{
    if ( argc != 2 )
    {
        std::cerr << "Arguments missing." << std::endl;
        std::cerr << "Usage: Lab06 <filename>" << std::endl;
        
        return 1;
    }
    
    DataWrapper lWrapper;
    
    if ( !lWrapper.load( argv[1] ) )
    {
        std::cerr << "Cannot load data file " << argv[1] << std::endl;
        
        return 2;
    }
    
    std::cout << "Data loaded." << std::endl;
    
#ifdef P1
    
    testP1( lWrapper );
    
#endif
    
#ifdef P2
        
    testP2( lWrapper );
    
#endif

    return 0;
}
