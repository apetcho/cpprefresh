#include "index.hpp"

/** @todo ... */

/** */
std::fstream& IndexEntry::write_at(std::fstream& strm, long pos) const{
    strm.seekg(pos);
    strm.write((char*)&key, sizeof(key));
    strm.write((char*)&recNr, sizeof(recNr));
    return strm;
}
