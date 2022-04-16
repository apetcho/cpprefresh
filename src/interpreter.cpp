#include<algorithm>
#include<cctype>

#include "interpreter.hpp"

double Statement::find_value(std::string& name){
    Node tmp{name};
    std::list<Node>::iterator iter = std::find(
        kvlist.begin(), kvlist.end(), tmp
    );

    if(iter != kvlist.end()){
        return iter->value;
    }else{
        issue_error("Unknown variable");
    }
    return 0.0;
}

// ----
void Statement::process_node(const std::string& name, double val){
    Node tmp{name, val};
    std::list<Node>::iterator iter = std::find(
        kvlist.begin(), kvlist.end(), tmp
    );
    if(iter != kvlist.end()){
        iter->value = val;
    }else{
        kvlist.pop_front(tmp);
    }
}

// ----
void Statement::read_key(std::string& name){
    int i=0;
    char *buf;
    if(isspace(ch)){
        std::cin >> ch;     // skip blanks;
    }
    if(isalpha(ch)){
        while(isalnum(ch)){
            buf[i++] = ch;
            std::cin.get(ch);
        }
        buf[i] = '\0';
        name = std::string(buf);
    }else{
        issue_error("Identifier expected");
    }
}
