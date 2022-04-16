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
