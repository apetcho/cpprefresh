// Defines the classes Acoount, DepositAccount, and SavingAccount
// with virtual read and write methods
#ifndef __MY_ACCOUNT_H_
#define __MY_ACCOUNT_H_
#include<iostream>
#include<fstream>

#include "myexceptions.hpp"

/** @todo .... */

enum class AccountType {ACCOUNT, DEP_ACC, SAV_ACC };

// --------------------------------------------------------------------
// ----- class Account                                            -----
// --------------------------------------------------------------------
class Account{
private:
    std::string name;       // Account holder
    unsigned long nr;       // Account number
    double balance;         // Balance of account


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

// --------------------------------------------------------------------
// ----- class DepositAccount                                     -----
// --------------------------------------------------------------------
class DepositAccount : public Account{
private:
    long limit; /** @todo XXX */
    long deb;   /** @todo XXX */
    /** @todo ...*/
    /* Data memebers, constructor, ...*/

    // ---
    AccountType get_account_type() const {
        return AccountType::DEP_ACC;
    }

    // ---
    std::ostream& write(std::ostream& strm) const;
    std::istream& read(std::istream& strm);

};

// --------------------------------------------------------------------
// ----- class SavingAccount                                      -----
// --------------------------------------------------------------------
class SavingAccount: public Account{
    /** @todo ... */
    /* Data members, constructor, ... */

    // ---
    AccountType get_account_type() const {
        return AccountType::SAV_ACC;
    }

    // ---
    std::ostream& write(std::ostream& strm) const;
    std::istream& read(std::istream& strm);
};

// --------------------------------------------------------------------
// ----- class AccountFile                                        -----
// --------------------------------------------------------------------
class AccountFile{
private:
    std::fstream stream;        // File stream
    std::string name;           // File name

public:
    AccountFile(const std::string& fname) throw(OpenError);
    ~AccountFile(){ stream.close(); }

    long append(Account& account) throw(WriteError);
    Account* retrieve(long pos) throw(ReadError);
};

#endif
