
// COS30008, tutorial 4, 2024

#include <iostream>

#include "Account.h"
#include "BankAccount.h"

int main()
{
    BankAccount lAccount( 12345 );
    
    std::cout << "Balance: " << lAccount.balance() << std::endl;
    
    // test dynamic method invocation
    
    Account& lBankAccount = lAccount;
    
    if ( lBankAccount.withdraw( 50.0 ) )
    {
        std::cout << "Instant credit. Wow!" << std::endl;
    }
    else
    {
        std::cout << "Sorry, not enough funds available. :(" << std::endl;
    }
    
    return 0;
}
