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
