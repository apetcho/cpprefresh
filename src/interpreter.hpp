#ifndef __MY_INTERPRETER_H__
#define __MY_INTERPRETER_H__

#include<iostream>
#include<string>
#include<list>

class Statement;

class Node{
private:
    std::string key;
    double value;
public:
    Node(std::string name="", double val=0.0) : key(name), value(val){}

private:
    friend class Statement;

    friend bool operator==(const Node& lhs, const Node& rhs){
        return lhs.key == rhs.key;
    }

    friend std::ostream& operator<<(std::ostream& out, const Node& node){
        out << node.key << " = " << node.value << std::endl;
        return out;
    }
};

// ----
class Statement{
public:
    Statement(){}

    //
    void get_statement();

private:
    std::list<Node> kvlist;
    char ch;

private:
    double factor();
    double term();
    double expression();
    void read_key(std::string& key);

    void issue_error(const char *message){
        std::cerr << message << std::endl;
        exit(EXIT_FAILURE);
    }

    double find_value(std::string&);
    void process_node(std::string&, double);

    // ---
    friend std::ostream& operator<<(std::ostream& out, const Statement& stmnt){
        //std::list<Node>::const_iterator iter = stmnt.kvlist.begin();
        auto kvals = stmnt.kvlist;
        for(auto const node: kvals){
            out << node.value;
        }
        out << std::endl;
        return out;
    }
};

#endif
