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
