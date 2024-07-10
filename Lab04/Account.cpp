
// COS30008, tutorial 4, 2024

#include "Account.h"

Account::Account( uint64_t aNumber, double aBalance ) noexcept :
    fNumber(aNumber),
    fBalance(aBalance)
{}

bool Account::deposit( double aAmount ) noexcept
{
    fBalance += aAmount;
    
    return true;
}

bool Account::withdraw( double aAmount ) noexcept
{
    fBalance -= aAmount;
    
    return true;
}
