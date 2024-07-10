
// COS30008, tutorial 4, 2024

#pragma once

#include "Account.h"

class BankAccount : public Account
{
private:
    double fInterestRate;
    
public:
    BankAccount( uint64_t aNumber, double aBalance = 0.0, double aInterestRate = 0.0 ) noexcept;
    
    virtual ~BankAccount() override {}

    double& interest() noexcept { return fInterestRate; }
    
    bool withdraw( double aAmount ) noexcept override;

    bool creditInterest( double aInterval = 31.0 / 365.0 ) noexcept;
    bool applyServiceFee( double aFee = 5.0 ) noexcept;

    // inherited from Account
    // uint64_t number() const noexcept;
    // double balance() const noexcept;
    // bool deposit( double aAmount ) noexcept;
    // bool withdraw( double aAmount ) noexcept;
};
