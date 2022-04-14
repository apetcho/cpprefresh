#ifndef __DBAPP_H__
#define __DBAPP_H__
#include<iostream>
#include<fstream>
#include<string>

// -----
class Personal{
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

    std::istream& readfrom_console(std::istream& strm);

    friend std::istream& operator>>(std::istream& strm, Personal& perso){
        return perso.readfrom_console(strm);
    }
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
};

#endif
