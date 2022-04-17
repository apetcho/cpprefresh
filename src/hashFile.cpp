#include "hashFile.hpp"

std::fstream& HashEntry::write(std::fstream& strm){
    /** @todo */
}

// ---
std::fstream& HashEntry::read(std::fstream& strm){
    /** @todo */
}

// ---
std::fstream& HashEntry::write_at(std::fstream& strm, unsigned long pos){
    /** @todo */
}

// ---
std::fstream& HashEntry::read_at(std::fstream& strm, unsigned long pos){
    /** @todo */
}

// ---
HashFile::HashFile(const std::string fname, unsigned long n) throw(OpenError){
    /** @todo */
}

// ---
void HashFile::insert(HashEntry& record) throw(ReadError, WriteError){
    /** @todo */
}

// ---
HashEntry& HashFile::retrieve(unsigned long key) throw(ReadError){
    /** @todo */
}

// ---
void HashFile::display(){
    /** @todo */
}
