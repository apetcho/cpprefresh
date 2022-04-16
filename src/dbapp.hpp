#ifndef __MY_DBAPP_H__
#define __MY_DBAPP_H__

#include<iostream>
#include<fstream>
#include<string>

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
class Personal{
public:
    Personal();
    Personal(std::string, std::string, std::string, int, long);
    void write_to_file(std::fstream& stream) const;
    void read_from_file(std::fstream& stream);
    void read_key();

    // ---
    int size() const {
        return 9 + name.size() + city.size() + sizeof(year) + sizeof(salary);
    }

    friend bool operator==(const Personal& lhs, const Personal& rhs){
        return lhs.ssn == rhs.ssn;
    }

    ~Personal(){}

protected:
    int year;
    long salary;
    std::string ssn;
    std::string name;
    std::string city;

    std::ostream& write_legibly(std::ostream& strm) const;
    friend std::ostream& operator<<(std::ostream& strm, const Personal& perso){
        return perso.write_legibly(strm);
    }

    std::istream& read_from_console(std::istream& strm);

    friend std::istream& operator>>(std::istream& strm, Personal& perso){
        return perso.read_from_console(strm);
    }
};

// -------------------------------------------------------------------
// -----  STUDENT                                                -----
// -------------------------------------------------------------------
class Student: public Personal {
public:
    Student();
    Student(std::string, std::string, std::string, int, long, std::string);

    void write_to_file(std::fstream& strm) const;
    void read_from_file(std::fstream& strm);
    int size() const{
        return Personal::size() + major.size();
    }


protected:
    std::string major;
    std::ostream& write_legibly(std::ostream& stream) const;

    friend std::ostream& operator<<(std::ostream& strm, Student& student){
        return student.write_legibly(strm);
    }

    std::istream& read_from_console(std::istream& strm);

    friend std::istream& operator>>(std::istream& strm, Student& student){
        return student.read_from_console(strm);
    }
};

// ---------------------------------------------------------------------

template<typename T>
class Database {
private:
    std::fstream database;
    std::string fname;

private:
    std::ostream& print(std::ostream& strm);
    void add(T& );
    bool find(const T&);
    void modify(const T&);

    friend std::ostream& operator<<(std::ostream& strm, Database& db){
        return db.print(strm);
    }

public:
    Database(){}
    void run();
    ~Database(){}
};

// ---- IMPLEMENTATION -----
template<typename T>
void Database<T>::add(T& object){
    database.open(fname, std::ios::in|std::ios::out);
    database.clear();
    database.seekg(0, std::ios::end);
    object.write_to_file(database);
    database.close();
}

// *****
template<typename T>
void Database<T>::modify(const T& object){
    T tmp;
    database.open(fname, std::ios::in|std::ios::out);
    database.clear();
    while(!database.eof()){
        tmp.read_from_file(database);
        if(tmp == object){ /** @todo check size*/
            std::cin >> tmp;
            database.seekg(-object.size(), std::ios::cur);
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
bool Database<T>::find(const T& object){
    T tmp;
    database.open(fname, std::ios::in);
    database.clear();
    while(!database.eof()){
        tmp.read_from_file(database);
        if(tmp == object){
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
    std::cout.flush();
}

template<typename T>
void Database<T>::run(){
    std::cout << CYAN << "Enter filename:" << NORMAL << std::endl;
    std::cout << GREEN << PROMPT << NORMAL;
    std::cout.flush();
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
        std::cout.flush();
        std::cin >> opt;
        cmd = OptionCmd{opt};
        std::cin.ignore();
        std::cout.flush();
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

#endif
