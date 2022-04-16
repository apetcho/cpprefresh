#ifndef __MY_INDEX_H_
#define __MY_INDEX_H_

#include<fstream>
#include<iostream>

// --------------------------------------------------------------------
// ----- class IndexEntry                                         -----
// --------------------------------------------------------------------
class IndexEntry{
private:
    long key;       // Key
    long recNr;     // Offset

public:
    // --- ctor
    IndexEntry(long k=0L, long n=0L) : key(k), recNr(n) {}

    /** @todo Access methods ... and :*/
    int record_size() const{
        return sizeof(key) + sizeof(recNr);
    }

    std::fstream& write(std::fstream& strm) const;
    std::fstream& read(std::fstream& strm);
    std::fstream& write_at(std::fstream& strm, long pos) const;
    std::fstream& read_at(std::fstream& strm, long pos); 
};

#endif
