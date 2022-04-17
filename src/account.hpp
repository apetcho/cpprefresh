// Defines the classes Acoount, DepositAccount, and SavingAccount
// with virtual read and write methods
#ifndef __MY_ACCOUNT_H_
#define __MY_ACCOUNT_H_
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

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
    Account(
        const std::string cname="X",
        unsigned long cnr = 1111111L,
        double cbalance = 0.0
    ) : name(cname), nr(cnr), balance(cbalance){}

    virtual ~Account(){}

    // Access methods
    long get_accountno() const { return nr; }
    void set_accountno(unsigned long n){ nr = n; }
    double get_balance() const  { return balance; }
    void set_balance(double value){ balance = value; }
    std::string get_account_name() const { return name; }
    void set_account_name(const std::string& name){
        this->name = name;
    }

    //  ---
    virtual AccountType get_account_type() const {
        return AccountType::ACCOUNT;
    }

    // ---
    virtual std::ostream& write(std::ostream& strm) const;
    virtual std::istream& read(std::istream& strm);

    // ---
    virtual void display() const {
        std::cout << std::fixed << std::setprecision(2)
            << "--------------------------------------------------\n"
            << " Account holder:        " << name       << std::endl
            << " Account number:        " << nr         << std::endl
            << " Balance of account:    " << balance    << std::endl
            << "--------------------------------------------------\n"
            << std::endl;
    }
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
