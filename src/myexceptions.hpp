/** Excpetion classes for file access */
#ifndef __MY_EXCEPTIONS_H_
#define __MY_EXCEPTIONS_H_

#include<string>
#include<iostream>

// --------------------------------------------------------------------
// ----- class FileError                                          -----
// --------------------------------------------------------------------
class FileError{
private:
    std::string filename;

public:
    FileError(const std::string& fname) : filename(fname){}

    std::string get_name() const { return filename; }
};


#endif
