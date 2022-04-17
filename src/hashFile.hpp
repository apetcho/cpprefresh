#ifndef __MY_HASH_FILE_H_
#define __MY_HASH_FILE_H_

#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>

#include "myexceptions.hpp"


// ---------------------------------------------------------------------
// ----- class HashEntry
// ---------------------------------------------------------------------
class HashEntry{
private:
    unsigned long nr;
    char name[30+1];

public:
    HashEntry(unsigned long n=0L, const std::string& s="")
    : nr(n){
        strncpy(name, s.c_str(), 29);
        name[30] = '\0';
    }

    long getNr() const { return nr; }
    void setNr(unsigned long n){ nr = n; }
    std::string getName() const { return name; }
    void setName(const std::string& s){
        strncpy(name, s.c_str(), 29);
        name[30] = '\0';
    }

    int getSize() const {
        return (sizeof(long) + sizeof(name));
    }

    std::fstream& write(std::fstream& fs);
    std::fstream& read(std::fstream& fs);

    std::fstream& write_at(std::fstream& fs, unsigned long pos);
    std::fstream& read_at(std::fstream& fs, unsigned long pos);

    virtual void display(){
        std::cout << std::endl
            << std::fixed << std::setprecision(2)
            << "--------------------------------------------\n"
            << " Client number:             " << nr << std::endl
            << " Client:                    " << name << std::endl
            << "--------------------------------------------\n"
            << std::endl;

        std::cin.get();
    }
};


// ---------------------------------------------------------------------
// ----- class HashEntry
// ---------------------------------------------------------------------
class HashFile{
private:
    std::fstream stream;
    std::string name;
    unsigned long b;

protected:
    unsigned long hash_func(unsigned long key){ key % b; }

public:
    HashFile(const std::string s, unsigned long n) throw(OpenError);

    void insert(HashEntry& record) throw(ReadError, WriteError);
    HashEntry& retrieve(unsigned long key) throw(ReadError);
    void display();
};

#endif
