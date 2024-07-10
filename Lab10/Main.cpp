
// COS30008, Tutorial 10, 2024

#include <iostream>

#define P1
#define P2
#define P3
#define P4

#include "Stack.h"

class Data
{
private:
    std::string fName;
    std::string fType;
    int fValue;
    
public:
    Data( const char* aName = "", const char* aType = "", int aValue = 0 ) :
        fName(aName),
        fType(aType),
        fValue(aValue)
    {}

    friend std::ostream& operator<<( std::ostream& s, const Data& o );
};

std::ostream& operator<<( std::ostream& s, const Data& o )
{
    return s << o.fName << " " << o.fType << " " << o.fValue;
}

void testStack()
{

#ifdef P1

    std::cout << "Basic Test:" << std::endl;

    Stack<Data> lStack1;

    std::cout << "push elements:" << std::endl;

    for ( int i = 1; i <= 30; i++ )
    {
        lStack1.push( Data( "n", "int", i ) );
    }

    std::cout << "pop elements:" << std::endl;
    
    std::optional lValue1 = lStack1.top();

    while ( lValue1 )
    {
        std::cout << "\t" << lValue1.value() << std::endl;
    
        lStack1.pop();

        lValue1 = lStack1.top();
    }

    if ( lValue1 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

#endif

#ifdef P2

    std::cout << "Emplace Test:" << std::endl;

    Stack<Data> lStack2;

    std::cout << "push/emplace elements:" << std::endl;

    for ( int i = 1; i <= 30; i++ )
    {
        if ( i % 2 == 0 )
        {
            lStack2.push( Data( "n", "int", i ) );
        }
        else
        {
            lStack2.emplace( "n", "int", i );
        }
    }

    std::cout << "pop elements:" << std::endl;

    std::optional lValue2 = lStack2.top();

    while ( lValue2 )
    {
        std::cout << "\t" << lValue2.value() << std::endl;

        lStack2.pop();

        lValue2 = lStack2.top();
    }

    if ( lValue2 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

#endif

#ifdef P3

    std::cout << "Copy test:" << std::endl;

    Stack<Data> lStack3;

    std::cout << "push elements:" << std::endl;

    for ( int i = 1; i <= 30; i++ )
    {
        lStack3.push( Data( "n", "int", i ) );
    }

    std::cout << "pop elements:" << std::endl;

    Stack<Data> lCopy3 = lStack3;
    
    std::optional lValue3 = lCopy3.top();

    while ( lValue3 )
    {
        std::cout << "\t" << lValue3.value() << std::endl;

        lCopy3.pop();

        lValue3 = lCopy3.top();
    }

    if ( lValue3 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }
    
    std::cout << "Can't pop elements:" << std::endl;

    lStack3 = lCopy3;

    lValue3 = lStack3.top();

    if ( lValue3 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

#endif

#ifdef P4

    std::cout << "Move test:" << std::endl;

    Stack<Data> lStack4;

    std::cout << "push elements:" << std::endl;

    for ( int i = 1; i <= 30; i++ )
    {
        lStack4.push( Data( "n", "int", i ) );
    }

    std::cout << "Can't pop elements:" << std::endl;
    
    Stack<Data> lMove4 = std::move(lStack4);
    
    std::optional lValue4 = lStack4.top();

    if ( lValue4 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

    std::cout << "pop elements:" << std::endl;

    lStack4 = std::move(lMove4);

    lValue4 = lStack4.top();

    while ( lValue4 )
    {
        std::cout << "\t" << lValue4.value() << std::endl;

        lStack4.pop();

        lValue4 = lStack4.top();
    }

    if ( lValue4 )
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        std::cout << "success" << std::endl;
    }

#endif
}

int main()
{
    testStack();
    
    return 0;
}
