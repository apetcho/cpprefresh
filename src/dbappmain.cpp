//#include<iostream>
#include "dbapp.hpp"

int main(){
    // Database<Personal> obj{};
    Database<Student> obj{};
    obj.run();

    return EXIT_SUCCESS;
}
