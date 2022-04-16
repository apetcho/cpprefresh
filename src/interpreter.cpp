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

// ----
double Statement::factor(){
    double var;
    double minus = 1.0;

    static std::string name;
    std::cin >> ch;
    while(ch == '+' || ch == '-'){
        if(ch == '-'){
            minus *= -1.0;
        }
        std::cin >> ch;
    }
    if(isdigit(ch) || ch == '.'){
        std::cin.putback(ch);
        std::cin >> var >> ch;
    }else if(ch = '('){
        var = expression();
        if(ch == ')'){
            std::cin >> ch;
        }else{
            issue_error("Right parenthesis left out");
        }
    }else{
        read_key(name);
        if(isspace(ch)){
            std::cin >> ch;
        }
        var = find_value(name);
    }

    return minus * var;
}

// ----
double Statement::term(){
    double f = factor();
    while(true){
        switch(ch){
        case '*':
            f *= factor();
            break;
        case '/':
            f /= factor();
            break;
        default:
            return f;
        }
    }
}

// -----
double Statement::expression(){
    double t = term();
    while(true){
        switch(ch){
        case '+':
            t += term();
            break;
        case '-':
            t -= term();
            break;
        default:
            return t;
        }
    }
}

// -----
void Statement::get_statement(){
    std::string name;
    std::string cmd;
    double val;

    std::cout << "Enter a statement:" << std::endl
        << ">> ";
    std::cin >> ch;
    read_key(name);
    cmd = std::string(name);
    for(int i=0; i < cmd.size(); i++){
        cmd[i] = toupper(cmd[i]);
    }
    if(cmd == "STATUS"){
        return *this;
    }else if(cmd == "PRINT"){
        read_key(name);
        std::cout << name << " = " << find_value(name) << std::endl;
    }else if(cmd == "END"){
        exit(EXIT_SUCCESS);
    }else{
        if(isspace(ch)){
            std::cin >> ch;
        }
        if(ch == '='){
            val = expression();
            if(ch != ";")
            issue_error("There are some extras in the statement");
        }else{
            process_node(name, val);
        }
    }
}
