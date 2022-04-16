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
