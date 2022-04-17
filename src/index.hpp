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
    long recPos;     // Offset

public:
    // --- ctor
    IndexEntry(long k=0L, long n=0L) : key(k), recPos(n) {}

    /** @todo Access methods ... and :*/
    long get_key() const{ return key; }
    void set_key(long key){this->key = key; }
    void set_pos(long pos){this->recPos = pos; }
    long get_pos() const { return recPos; }

    int record_size() const{
        return sizeof(key) + sizeof(recPos);
    }

    std::fstream& write(std::fstream& strm) const;
    std::fstream& read(std::fstream& strm);
    std::fstream& write_at(std::fstream& strm, long pos) const;
    std::fstream& read_at(std::fstream& strm, long pos);

    void display() const {
        std::cout
            << " Account Nr: " << key
            << "   Position: " << recPos << std::endl;
    }
};

// --------------------------------------------------------------------
// ----- class IndexFile                                          -----
// --------------------------------------------------------------------
class IndexFile{
private:
    std::fstream index;
    std::string name;               // Filename of index

public:
    IndexFile(const std::string& fname) throw(OpenError);
    ~IndexFile(){ index.close(); }

    void insert(long key, long pos) throw(ReadError, WriteError);
    long search(long key) throw (ReadError);
    void retrieve(IndexEntry& entry, long pos) throw(ReadError);
    void display() throw(ReadError);
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

    bool insert(Account& account) throw(ReadError, WriteError);
    Account* retrieve(long key);
};

#endif
