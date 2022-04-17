#include "index.hpp"

/** @todo add documentation */
std::fstream& IndexEntry::write_at(std::fstream& strm, long pos) const{
    strm.seekg(pos);
    strm.write((char*)&key, sizeof(key));
    strm.write((char*)&recPos, sizeof(recPos));
    return strm;
}

/** @todo add documentation */
std::fstream& IndexEntry::read_at(std::fstream& strm, long pos){
    strm.seekg(pos);
    strm.read((char*)&key, sizeof(key));
    strm.read((char*)&recPos, sizeof(recPos));
    return strm;
}

/** @todo add documentation */
std::fstream& IndexEntry::write(std::fstream& strm) const {
    strm.write((char*)&key, sizeof(key));
    strm.write((char*)&recPos, sizeof(recPos));
    return strm;
}

/** @todo add documentation */
std::fstream& IndexEntry::read(std::fstream& strm){
    strm.read((char*)&key, sizeof(key));
    strm.read((char*)&recPos, sizeof(recPos));
    return strm;
}

/** @todo add documentation */
IndexFile::IndexFile(const std::string& fname){
    std::ios::openmode mode = std::ios::in|std::ios::out|std::ios::binary;

    index.open(fname.c_str(), mode);
    if(!index){ // If the file doese not exist
        index.clear();
        mode |= std::ios::trunc;
        index.open(fname.c_str(), mode);
        if(!index){ return; }
    }else{
        name = fname;
    }
}

/** @todo add documentation */
void IndexFile::display() throw(ReadError){
    IndexEntry entry;
    index.seekg(0L);
    if(!index){
        throw ReadError("IndexFile: Setting the get pointer");
    }

    std::cout << std::endl << "The Index: " << std::endl;
    while(true){
        if(!entry.read(index)){ break;}
        entry.display();
    }
    if(!index.eof()){ throw ReadError(name); }
    index.clear();
}

/** @todo add documentation */
long IndexFile::search(long k) throw(ReadError){
    IndexEntry entry;
    long key;
    long mid, begin=0, end;
    int size = entry.record_size();

    index.clear();
    index.seekg(0L, std::ios::end);
    end = index.tellg()/size;

    if(!index){ throw ReadError(name); }

    if( end == 0){ return -1; }

    end -= 1;

    while(begin < end){
        mid = (begin + end + 1)/2;
        entry.read_at(index, mid*size);
        if(!index){throw ReadError(name);}

        key = entry.get_key();
        if(k < key){ end = mid - 1; }
        else{ begin = mid; }
    }

    entry.read_at(index, begin * size);
    if(!index){throw ReadError(name); }

    if(k == entry.get_key()){ return begin * size; }
    else{ return -1; }
}

// --------------------------------------------------------------------
// ----- IndexFile::insert()                                      -----
// --------------------------------------------------------------------
void IndexFile::insert(long k, long n) throw(ReadError, WriteError){
    IndexEntry entry;
    int size = entry.record_size();     // length of index entry
    index.clear();
    index.seekg(0, std::ios::end);
    long nr = index.tellg();            // Get file length, o0 if file is empty

    if(!index){ throw ReadError(name); }

    nr -= size;                         // Last entry
    bool found = false;
    while(nr >= 0 && !found){
        if(!entry.read_at(index, nr)){ throw ReadError(name); }

        if( k < entry.get_key()){
            entry.write_at(index, nr+size);
            nr -= size;
        }else{ found = true; }
    }

    entry.set_key(k);
    entry.set_pos(n);
    entry.write_at(index, nr + size);

    if(!index){throw WriteError(name); }
}

/** @todo add documentation */
void IndexFile::retrieve(IndexEntry& entry, long pos) throw(ReadError){
    index.clear();
    if(!entry.read_at(index, pos)){
        throw ReadError(name);
    }
}

// --------------------------------------------------------------------
// ----- IndexFileSystem::insert()                                -----
// --------------------------------------------------------------------
void IndexFileSystem::insert(Account& account){
    /** @todo: see p. 654 */
}
