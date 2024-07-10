
// COS30008, tutorial 4, 2024

#pragma once

#include <cstdint>

class Account
{
private:
    uint64_t fNumber;
    double fBalance;
    
public:
    
    Account( uint64_t aNumber, double aBalance = 0.0 ) noexcept;
    
    virtual ~Account() {}
    
    uint64_t number() const noexcept { return fNumber; }
    double balance() const noexcept { return fBalance; }
    
    bool deposit( double aAmount ) noexcept;

    virtual bool withdraw( double aAmount ) noexcept;
};
