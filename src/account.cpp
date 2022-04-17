#include <typeinfo>
#include "account.hpp"

// --------------------------------------------------------------------
// ----- Account::write()                                         -----
// --------------------------------------------------------------------
std::ostream& Account::write(std::ostream& strm) const {
    strm << name << '\0';
    strm.write((char*)&nr, sizeof(nr));
    strm.write((char*)&balance, sizeof(balance));
    return strm;
}

// --------------------------------------------------------------------
// ----- Account::read()                                          -----
// --------------------------------------------------------------------
std::istream& Account::read(std::istream& strm){
    std::getline(strm, name, '\0');
    strm.read((char*)&nr, sizeof(nr));
    strm.read((char*)&balance, sizeof(balance));
    return strm;
}

// --------------------------------------------------------------------
// ----- DepositAccount::write()                                  -----
// --------------------------------------------------------------------
std::ostream& DepositAccount::write(std::ostream& strm) const{
    if(!Account::write(strm)){
        return strm;
    }
    strm.write((char*)&limit, sizeof(limit));
    strm.write((char*)&interest, sizeof(interest));
    return strm;
}

// --------------------------------------------------------------------
// ----- DepositAccount::read()                                   -----
// --------------------------------------------------------------------
std::istream& DepositAccount::read(std::istream& strm){
    if(!Account::read(strm)){ return strm; }
    strm.read((char*)&limit, sizeof(limit));
    strm.read((char*)&interest, sizeof(interest));
    return strm;
}

// --------------------------------------------------------------------
// ----- SavingAccount::write()                                   -----
// --------------------------------------------------------------------
std::ostream& SavingAccount::write(std::ostream& strm) const {
    if(!Account::write(strm)){
        return strm;
    }
    strm.write((char*)&interest, sizeof(interest));
    return strm;
}

// --------------------------------------------------------------------
// ----- SavingAccount::read()                                    -----
// --------------------------------------------------------------------
std::istream SavingAccount::read(std::istream& strm){
    if(!Account::read(strm)){ return strm; }
    strm.read((char*)&interest, sizeof(interest));
    return strm;
}

// --------------------------------------------------------------------
// ----- AccountFile::AccountFile() ctor                          -----
// --------------------------------------------------------------------
AccountFile::AccountFile(const std::string& nm) throw(OpenError){
    std::ios::openmode mode = std::ios::in | std::ios::out |
        std::ios::app | std::ios::binary;
    stream.open(nm.c_str(), mode);
    if(!stream){ throw OpenError(nm); }
    else{
        this->name = nm;
    }
}

// --------------------------------------------------------------------
// ----- AccountFile::display()                                   -----
// --------------------------------------------------------------------
void AccountFile::display() throw(ReadError){
    Account account;
    Account *pAccount = nullptr;
    DepositAccount depAcc;
    SavingAccount savAcc;
    AccountType accType;
    int accId;

    if(!stream.seekg(0L)){ throw ReadError(name);}

    std::cout << "\nThe account file: " << std::endl;

    while(stream.read((char*)&accId, sizeof(int))){
        accType = AccountType{accId};
        switch(accType){
        case AccountType::ACCOUNT:
            pAccount = &account;
            break;
        case AccountType::DEP_ACC:
            pAccount = &depAcc;
            break;
        case AccountType::SAV_ACC:
            pAccount = &savAcc;
            break;
        default:
            std::cerr << "Invalid flag in account file" << std::endl;
            exit(EXIT_FAILURE);
        }

        if(!pAccount->read(stream)){ break; }
        pAccount->display();
        std::cin.get();         // Go on with return 
    }
    if(!stream.eof()){ throw ReadError(name); }
    stream.clear();
}

// --------------------------------------------------------------------
// ----- AccountFile::append()                                    -----
// --------------------------------------------------------------------
long AccountFile::append(Account& account) throw(WriteError){
    stream.seekp(0L, std::ios::end);    // Seek to end
    long pos = stream.tellg();          // Save the position

    if(!stream){ throw WriteError(name); }

    AccountType accId = account.get_account_type();
    int id = (int)accId;
    stream.write((char*)&id, sizeof(int));
    if(!stream){ throw WriteError(name); }
    else{ account.write(stream); }

    if(!stream){ throw WriteError(name); }
    else{ return pos; }
}

// --------------------------------------------------------------------
// ----- AccountFile::retrieve()                                  -----
// --------------------------------------------------------------------
Account* AccountFile::retrieve(long pos) throw(ReadError){
    stream.clear();
    stream.seekg(pos);      // Set the get pointer

    if(!stream){ throw ReadError(name); }
    AccountType accType;
    int accId;
    stream.read((char*)&accId, sizeof(accId));
    accType = AccountType{accId};

    if(!stream){ throw ReadError(name); }

    Account *buf;
    switch(accType){
    case AccountType::ACCOUNT:
        buf = new Account;
        break;
    case AccountType::SAV_ACC:
        buf = new SavingAccount;
        break;
    case AccountType::DEP_ACC:
        buf = new DepositAccount;
        break;
    }

    if(!(buf->read(stream))){ throw ReadError(name); }

    return buf;
}
