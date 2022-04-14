#include<iomanip>
#include<variant>
#include<type_traits>
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
    strm << YELLOW << "SSN = " << NORMAL << ssn << ", ";
    strm << YELLOW << "Name = " << NORMAL << name << ", ";
    strm << YELLOW << "City = " << NORMAL << city << ", ";
    strm << YELLOW << "Year = " << NORMAL << year << ", ";
    strm << YELLOW << "Salary = " << NORMAL << salary;

    return strm;
}

// -----
using var_t = std::variant<int&, long&, std::string&>;
struct VarVisitor {
    std::istream stream;
    std::string header;

    VarVisitor(std::istream& strm, const std::string& hdr)
    : stream(strm), header(hdr){}

    void operator()(int& vname){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        stream >> vname;
    }

    void operator()(long& vname){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        stream >> vname;
    }

    void operator()(std::string& vname){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        std::getline(stream, vname);
    }
};


static void read_console(std::istream& strm, std::string header, var_t var){
    VarVisitor visitor(strm, header);
    std::visit(var, visitor);
}


// *****
std::istream& Personal::read_from_console(std::istream& strm){
    std::cout.flush();
    var_t var = ssn;
    std::string header = "SSN:";
    read_console(strm, header, var);
    var = name;
    header = "Name:";
    read_console(strm, header, var);
    var = city;
    header = "City:";
    read_console(strm, header, var);
    var = year;
    header = "Birthyear:";
    read_console(strm, header, var);
    var = salary;
    header = "Salary:";
    read_console(strm, header, var);

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
void Student::write_to_file(std::fstream& strm) const{
    Personal::write_to_file(strm);
    strm << major << '\n';
    strm.flush();
}

// *****
void Student::read_from_file(std::fstream& strm){
    Personal::read_from_file(strm);
    std::getline(strm, major);
}

// *****
std::ostream& Student::write_legibly(std::ostream& strm) const {
    Personal::write_legibly(strm);
    strm << ", " << YELLOW << major << NORMAL ;
    return strm;
}

// ****
std::istream& Student::read_from_file(std::istream& strm){
    Personal::read_from_console(strm);
    var_t var = major;
    std::string header = "Major:";
    read_console(strm, header, var);

    return strm;
}

// --------------------------------------------------------------------
// -----   DATABASE                                               -----
// --------------------------------------------------------------------
template<typename T>
void Database<T>::add(T& obj){
    database.open(fname, std::ios::in|std::ios::out);
    database.clear();
    database.seekg(0, std::ios::end);
    obj.write_to_file(database);
    database.close();
}

// *****
template<typename T>
void Database<T>::modify(const T& obj){
    T tmp;
    database.open(fname, std::ios::in|std::ios::out);
    database.clear();
    while(!database.eof()){
        tmp.read_from_file(database);
        if(tmp == obj){ /** @todo check size*/
            std::cin >> tmp;
            database.seekg(-obj.size(), std::ios::cur);
            tmp.write_to_file(database);
            database.close();
            return;
        }
    }
    database.close();
    std::cout << "The record to be modified is not the the database\n";
}

// *****
template<typename T>
bool Database<T>::find(const T& obj){
    T tmp;
    database.open(fname, std::ios::in);
    database.clear();
    while(!database.eof()){
        tmp.read_from_file(database);
        if(tmp == obj){
            database.close();
            return true;
        }
    }

    database.close();
    return false;
}

// *****
template<typename T>
std::ostream& Database<T>::print(std::ostream& strm){
    T tmp;
    database.open(fname, std::ios::in);
    database.clear();
    while(true){
        tmp.read_from_file(database);
        if(database.eof()){break;}
        strm << tmp << std::endl;
    }
    database.close();
    return strm;
}
