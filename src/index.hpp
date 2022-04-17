#ifndef __MY_INDEX_H_
#define __MY_INDEX_H_

#include<fstream>
#include<iostream>
#include<string>
#include "myexceptions.hpp"
#include "account.hpp"

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
    long get_key() const; // ...
    void set_key(long k); // ...
    void set_pos(long n); // ...

    int record_size() const{
        return sizeof(key) + sizeof(recNr);
    }

    std::fstream& write(std::fstream& strm) const;
    std::fstream& read(std::fstream& strm);
    std::fstream& write_at(std::fstream& strm, long pos) const;
    std::fstream& read_at(std::fstream& strm, long pos); 
};

// --------------------------------------------------------------------
// ----- class IndexFile                                          -----
// --------------------------------------------------------------------
class IndexFile{
private:
    std::fstream index;
    std::string name;               // Filename of index

public:
    IndexFile(const std::string& fname);
    ~IndexFile(){ index.close(); }

    void insert(long key, long pos) throw(ReadError, WriteError);
    long search(long key);
    void retrieve(IndexEntry& entry, long pos);
};


// --------------------------------------------------------------------
// ----- class IndexFileSystem                                    -----
// --------------------------------------------------------------------
class IndexFileSystem : public AccountFile, public IndexFile {
private:
    std::string name;

public:
    IndexFileSystem(const std::string nm)
    : AccountFile(nm + ".prim"), IndexFile(nm + ".ind"){
        this->name = nm;
    }

    void insert(Account& account);
    Account* retrieve(long key);
};

#endif
