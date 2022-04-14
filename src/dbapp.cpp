#include "dbapp.h"

constexpr std::string RED = "\x1b[31m";
constexpr std::string GREEN = "\x1b[32m";
constexpr std::string YELLOW = "\x1b[33m";
constexpr std::string BLUE = "\x1b[34m";
constexpr std::string PURPLE = "\x1b[35m";
constexpr std::string CYAN = "\x1b[36m";
constexpr std::string NORMAL = "\x1b[m";
constexpr std::string PROMPT = ">> ";

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
    strm << ssn << '\n';
    strm << name << '\n';
    strm << city << '\n';
    strm << year << '\n';
    strm << salary << '\n';
    strm.flush();
}

// *****
void Personal::read_from_file(std::fstream& strm){
    std::getline(strm, ssn);
    std::getline(strm, name);
    std::getline(strm, city);
    std::getline(strm, year);
    std::getline(strm, salary);
}

// *****
void Personal::read_key(){
    std::cout << CYAN << "Enter SSN" << NORMAL << std::endl;
    std::cout << GREEN << PROMPT << NORMAL;
    std::getline(std::cin, ssn);
}

// *****
std::ostream& Personal::write_legibly(std::ostream& strm) const{
    strm << "SSN = " << ssn << ", ";
    strm << "Name = " << name << ", ";
    strm << "City = " << city << ", ";
    strm << "Year = " << year << ", ";
    strm << "Salary = " << salary;

    return strm;
}
