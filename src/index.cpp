#include "index.hpp"

/** @todo ... */

/** @todo add documentation */
std::fstream& IndexEntry::write_at(std::fstream& strm, long pos) const{
    strm.seekg(pos);
    strm.write((char*)&key, sizeof(key));
    strm.write((char*)&recNr, sizeof(recNr));
    return strm;
}

/** @todo add documentation */
std::fstream& IndexEntry::read_at(std::fstream& strm, long pos){
    strm.seekg(pos);
    strm.read((char*)&key, sizeof(key));
    strm.read((char*)&recNr, sizeof(recNr));
    return strm;
}
