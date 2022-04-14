#include "dbapp.h"

constexpr std::string RED = "\x1b[31m";
constexpr std::string GREEN = "\x1b[32m";
constexpr std::string YELLOW = "\x1b[33m";
constexpr std::string BLUE = "\x1b[34m";
constexpr std::string PURPLE = "\x1b[35m";
constexpr std::string CYAN = "\x1b[36m";
constexpr std::string NORMAL = "\x1b[m";

// --------------------------------------------------------------------
// -----   PERSONAL                                               -----
// --------------------------------------------------------------------
// *****
Personal::Personal()
: year(0), salary(0), ssn(""), name(""), city(""){}

// *****
Personal::Personal(
    std::string ssn, std::string name, std::string city,
    int year, long salary
){
    this->ssn = ssn;
    this->name = name;
    this->city = city;
    this->year = year;
    this->salary = salary;
}

// *****
void Personal::write_to_file(std::fstream& strm) const {
    strm << ssn;
    strm << name;
    strm << city;
    strm << year;
    strm << salary;
}
