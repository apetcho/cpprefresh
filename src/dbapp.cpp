#include<iomanip>
#include<variant>
#include<type_traits>
#include "dbapp.hpp"

const std::string RED = "\x1b[31m";
const std::string GREEN = "\x1b[32m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string PURPLE = "\x1b[35m";
const std::string CYAN = "\x1b[36m";
const std::string NORMAL = "\x1b[m";
const std::string PROMPT = ">> ";

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
    strm >> year;
    strm >> salary;
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
template<typename T>
static void read_console(std::istream& stream, std::string header, T& vname){
    if constexpr (std::is_same_v<T, int>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        stream >> vname;
    }else if constexpr(std::is_same_v<T, long>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        stream >> vname;
    }else if constexpr (std::is_same_v<T, std::string>){
        std::cout << CYAN << header << NORMAL;
        std::cout << GREEN << PROMPT;
        //const size_t len = 80;
        //char *value;
        //stream.getline(value, len);
        //value[len] = '\0';
        //vname = std::string(value);
        std::getline(stream, vname, '\n');
    }
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
std::istream& Student::read_from_console(std::istream& strm){
    Personal::read_from_console(strm);
    std::string header = "Major:";
    read_console(strm, header, major);

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

// *****
enum class OptionCmd{ ADD = 1, FIND, MODIFY, EXIT };

static void menu(){
    std::cout << PURPLE << "--------------------------------------\n" << NORMAL;
    std::cout << YELLOW << "     APPLICATION  COMMAND  MENU       \n" << NORMAL;
    std::cout << PURPLE << "--------------------------------------\n" << NORMAL;
    std::cout << BLUE << "1" << NORMAL << " --> ADD     \n";
    std::cout << BLUE << "2" << NORMAL << " --> FIND    \n";
    std::cout << BLUE << "3" << NORMAL << " --> MODIFY  \n";
    std::cout << BLUE << "4" << NORMAL << " --> EXIT    \n";
}

template<typename T>
void Database<T>::run(){
    std::cout << CYAN << "Enter filename:" << NORMAL << std::endl;
    std::cout << GREEN << PROMPT << NORMAL;
    std::cin >> fname;
    std::cin.ignore();
    database.open(fname, std::ios::in);
    if(database.fail()){
        database.open(fname, std::ios::out);
    }
    database.close();
    
    int opt;
    OptionCmd cmd;
    T record;

    do{
        menu();
        std::cout << std::endl << CYAN;
        std::cout << "Select an option" << NORMAL;
        std::cout << GREEN << PROMPT << NORMAL;
        std::cin >> opt;
        cmd = OptionCmd{opt};
        switch(cmd){
        case OptionCmd::ADD:
            std::cin >> record;
            add(record);
            break;
        case OptionCmd::FIND:
            record.read_key();
            std::cout << "The record is ";
            if(find(record) == false){ std::cout << "not "; }
            std::cout << "in the database" << std::endl;
            break;
        case OptionCmd::MODIFY:
            record.read_key();
            modify(record);
            break;
        case OptionCmd::EXIT:
            break;
        default:
            std::cout << "Wrong option" << std::endl;
            break;
        }
        std::cout << *this;
    }while(opt != 4);
}
