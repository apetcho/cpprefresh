// Defines the classes Acoount, DepositAccount, and SavingAccount
// with virtual read and write methods
#include<iostream>

/** @todo .... */

enum class AccountType {ACCOUNT, DEP_ACC, SAV_ACC };

// --------------------------------------------------------------------
// ----- class Account                                            -----
// --------------------------------------------------------------------
class Account{
private:
    //! @todo see ... chap. 18
    // Data member as previously. 

public:
    //! @todo see ... chap. 18
    // Constructor, access methods ...

    //  ---
    virtual AccountType get_account_type() const {
        return AccountType::ACCOUNT;
    }

    // ---
    virtual std::ostream& write(std::ostream& strm) const;
    virtual std::istream& read(std::istream& strm);
};
