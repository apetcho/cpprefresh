#ifndef __MY_DBAPP_H__
#define __MY_DBAPP_H__
#include<iostream>
#include<fstream>
#include<string>

// --------------------------------------------------------------------
// -----   PERSONAL                                               -----
// --------------------------------------------------------------------
class Personal{
public:
    Personal();
    Personal(std::string, std::string, std::string, int, long);
    virtual void write_to_file(std::fstream& stream) const;
    virtual void read_from_file(std::fstream& stream);
    void read_key();

    // ---
    virtual int size() const {
        return 9 + name.size() + city.size() + sizeof(year) + sizeof(salary);
    }

    friend bool operator==(const Personal& lhs, const Personal& rhs){
        return lhs.ssn == rhs.ssn;
    }

protected:
    int year;
    long salary;
    std::string ssn;
    std::string name;
    std::string city;

    virtual std::ostream& write_legibly(std::ostream& strm) const;
    friend std::ostream& operator<<(std::ostream& strm, const Personal& perso){
        return perso.write_legibly(strm);
    }

    virtual std::istream& read_from_console(std::istream& strm);

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

    void write_to_file(std::fstream& strm) const override;
    void read_from_file(std::fstream& strm) override;
    int size() const override{
        return Personal::size() + major.size();
    }

protected:
    std::string major;
    std::ostream& write_legibly(std::ostream& stream) const override;

    friend std::ostream& operator<<(std::ostream& strm, Student& student){
        return student.write_legibly(strm);
    }

    std::istream& read_from_console(std::istream& strm) override;

    friend std::istream& operator>>(std::istream& strm, Student& student){
        return student.read_from_console(strm);
    }
};

// -------------------------------------------------------------------
// -----  DATABASE                                               -----
// -------------------------------------------------------------------
template<typename T>
class Database {
public:
    Database(){
        this->fname = std::string("");
        this->database = std::fstream();
    }

    void run();

private:
    std::fstream database;
    std::string fname;

    std::ostream& print(std::ostream& strm);
    void add(T& );
    bool find(const T&);
    void modify(const T&);

    friend std::ostream& operator<<(std::ostream& strm, const Database& db){
        return db.print(strm);
    }
};

#endif
