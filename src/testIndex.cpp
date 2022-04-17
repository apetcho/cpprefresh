#include<iostream>
#include<string>

#include "index.hpp"
#include "account.hpp"

// ----------------------------
// -----   MAIN  DRIVER   -----
// ----------------------------
int main(int argc, char **argv){
    try{
        IndexFileSystem database("AccountTest");
        Account acc1("Vivi", 490UL, 123440.57);
        database.insert(acc1);

        SavingAccount acc2("Ulla", 590UL, 4321.19, 2.5);
        database.insert(acc2);

        DepositAccount acc3("Jeany", 390UL, 1234.20, 10000.0, 12.9);
        database.insert(acc3);

        database.IndexFile::display();
        std::cin.get();

        database.AccountFile::display();

        unsigned long key;

        std::cout << "Key? ";
        std::cin >> key;
        if(database.search(key) != -1){
            std::cout << "Key " << key << " found" << std::endl;
        }else{
            std::cout << "Key " << key << " not found" << std::endl;
        }

        Account* pAccount = database.retrieve(key);
        if(pAccount != nullptr){
            pAccount->display();
            delete pAccount;
            pAccount = nullptr;
        }else{
            std::cout << "Retrieving failed" << std::endl;
        }
    }catch(OpenError& err){
        std::cerr << "Error on opening the file: " << err.get_name()
            << std::endl;
        exit(EXIT_FAILURE);
    }catch(WriteError& err){
        std::cerr << "Error on writing into file: " << err.get_name()
            << std::endl;
        exit(EXIT_FAILURE);
    }catch(ReadError& err){
        std::cerr << "Error on reading from the file: "
            << err.get_name() << std::endl;
        exit(EXIT_FAILURE);
    }catch(...){
        std::cerr << "Unhandled exception" << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
