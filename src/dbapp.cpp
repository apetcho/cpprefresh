#include<iomanip>
#include<variant>
#include<type_traits>
#include "dbapp.hpp"

// --------------------------------------------------------------------
// -----   PERSONAL                                               -----
// --------------------------------------------------------------------
// *****
Personal::Personal()
: year(0), salary(0), ssn(""), name(""), city(""){}

// *****
Personal::Personal(
    std::string _ssn, std::string nm, std::string cty,
    int yr, long slry)
: year(yr), salary(slry), ssn(_ssn), name(nm), city(cty){}

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
    strm >> year;
    strm >> salary;
}

// *****
void Personal::read_key(){
    std::cout << CYAN << "Enter SSN" << NORMAL << std::endl;
    std::cout << GREEN << PROMPT << NORMAL;
    std::getline(std::cin, ssn);
    std::cout.flush();
}

// *****
std::ostream& Personal::write_legibly(std::ostream& strm) const{
    strm << YELLOW << "SSN = " << NORMAL << this->ssn << ", ";
    strm << YELLOW << "Name = " << NORMAL << this->name << ", ";
    strm << YELLOW << "City = " << NORMAL << this->city << ", ";
    strm << YELLOW << "Year = " << NORMAL << this->year << ", ";
    strm << YELLOW << "Salary = " << NORMAL << this->salary;
    strm.flush();
    return strm;
}

// -----
template<typename T>
static void read_console(std::istream& stream, std::string header, T& vname){
    if constexpr (std::is_same_v<T, int>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT << NORMAL;
        stream >> vname;
    }else if constexpr(std::is_same_v<T, long>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT << NORMAL;
        stream >> vname;
    }else if constexpr (std::is_same_v<T, std::string>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT << NORMAL;
        std::getline(stream, vname, '\n');
    }
    std::cout.flush();
}


// *****
std::istream& Personal::read_from_console(std::istream& strm){
    std::cout.flush();
    std::string header = "SSN:";
    read_console(strm, header, ssn);
    header = "Name:";
    read_console(strm, header, name);
    header = "City:";
    read_console(strm, header, city);
    header = "Birthyear:";
    read_console(strm, header, year);
    header = "Salary:";
    read_console(strm, header, salary);
    //std::cout.flush();
    return strm;
}

// --------------------------------------------------------------------
// -----   STUDENT                                                -----
// --------------------------------------------------------------------
// *****
Student::Student() : Personal(), major(""){}

// *****
Student::Student(
    std::string ssn, std::string nm, std::string cty,
    int yr, long slry, std::string maj
)
: Personal(ssn, nm, cty, yr, slry), major(maj) {}

// *****
void Student::write_to_file(std::fstream& strm) const override {
    Personal::write_to_file(strm);
    strm << major << '\n';
    strm.flush();
}

// *****
void Student::read_from_file(std::fstream& strm) override {
    Personal::read_from_file(strm);
    std::getline(strm, major);
}

// *****
std::ostream& Student::write_legibly(std::ostream& strm) const{
    Personal::write_legibly(strm);
    strm << ", " << YELLOW << "Major = " << NORMAL << this->major;
    //strm << ", " << YELLOW << major << NORMAL ;
    strm.flush();
    return strm;
}

// ****
std::istream& Student::read_from_console(std::istream& strm){
    Personal::read_from_console(strm);
    std::cin.ignore();
    //std::cout.flush();
    std::string header = "Major:";
    read_console(strm, header, major);
    std::cout.flush();
    return strm;
}
