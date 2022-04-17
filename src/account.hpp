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
    unsigned long get_accountno() const { return nr; }
    void set_accountno(unsigned long n){ nr = n; }
    double get_balance() const  { return balance; }
    void set_balance(double value){ balance = value; }
    const std::string& get_account_name() const { return name; }
    bool set_account_name(const std::string& nm){
        if(nm.size() < 1){ /* empty name */
            return false;
        }
        this->name = name;
        return true;
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
    double limit;               // Overdrawn limit
    double interest;            // Interest rate
    
public:
    DepositAccount(
        const std::string nm="X", unsigned long no=1111111L,
        double bal=0.0, double li=0.0, double ir=0.0
    ): Account(nm, no, bal), limit(li), interest(ir)
    {}

    // --- Access methods
    // limit, interest
    double get_limit() const { return limit; }
    double get_interest() const { return interest; }
    void set_limit(double limit){ this->limit = limit; }
    void set_interest(double interest){ this->interest = interest; }


    // ---
    AccountType get_account_type() const {
        return AccountType::DEP_ACC;
    }

    // ---
    std::ostream& write(std::ostream& strm) const;
    std::istream& read(std::istream& strm);

    // ---
    void display() const{
        Account::display();
        std::cout
            << " Overdrawn limit:        " << limit << std::endl
            << " Competitive interest:   " << interest << "\n"
            << "----------------------------------------------\n"
            << std::endl;
    }
};

// --------------------------------------------------------------------
// ----- class SavingAccount                                      -----
// --------------------------------------------------------------------
class SavingAccount: public Account{
private:
    double interest;            // Compound interest

public:
    SavingAccount(
        const std::string& nm="X",
        unsigned long n=1111111L,
        double bal=0.0,
        double ir=0.0
    ): Account(nm, n, bal), interest(ir)
    {}

    // ---
    double get_interest() const { return interest; }
    void set_interest(double ir){ interest = ir; } 

    // ---
    AccountType get_account_type() const {
        return AccountType::SAV_ACC;
    }

    // ---
    std::ostream& write(std::ostream& strm) const;
    std::istream& read(std::istream& strm);

    // ---
    void display() const {
        Account::display();
        std::cout
            << " Compount interest:     " << interest << std::endl
            << "------------------------------------------------\n"
            << std::endl;

    }
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

    // ---
    void display() throw(ReadError);
};

#endif
