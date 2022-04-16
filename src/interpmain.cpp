#include "interpreter.hpp"

void menu();

//
int main(){
    Statement stmt;
    menu();

    while(true){
        stmt.get_statement();
    }

    return EXIT_SUCCESS;
}

// ----
void menu(){
    std::cout << "This interpreter processes statement of the following "
        << "format: \n"
        << " <name> = <expr>;\n"
        << " print <name>\n"
        << " status\n"
        << " end\n"
        << std::endl;
}
