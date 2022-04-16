#include "account.hpp"

// --------------------------------------------------------------------
// ----- DepositAccount::write()                                  -----
// --------------------------------------------------------------------
std::ostream& DepositAccount::write(std::ostream& strm) const{
    if(!Account::write(strm)){
        return strm;
    }
    strm.write((char*)&limit, sizeof(limit));
    strm.write((char*)&deb, sizeof(deb));
    return strm;
}

// --------------------------------------------------------------------
// ----- DepositAccount::read()                                   -----
// --------------------------------------------------------------------
std::istream& DepositAccount::read(std::istream& strm){
    if(!Account::read(strm)){ return strm; }
    strm.read((char*)&limit, sizeof(limit));
    strm.read((char*)&deb, sizeof(deb));
    return strm;
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
    stream.write((char*)&id, sizeof(id));
    if(!stream){ throw WriteError(name); }
    else{ account.write(stream); }

    if(!stream){ throw WriteError(name); }
    else{ return pos; }
}
