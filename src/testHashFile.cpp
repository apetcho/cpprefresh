#include<iostream>
#include<string>

#include "hashFile.hpp"

// -----------------------------
// ------   MAIN DRIVER   ------
// -----------------------------
int main(int argc, char **argv){
    try{
        HashFile hash("Client.fle", 7); // Address space of length 7
        std::cout << "\nInsert: " << std::endl;
        HashEntry kde(3L, "Vivi");
        hash.insert(kde);

        kde.setNr(10L);
        kde.setName("Peter");
        hash.insert(kde);

        kde.setNr(17L);
        kde.setName("Alexa");
        hash.insert(kde);

        kde.setNr(21L);
        kde.setName("Peter");
        hash.insert(kde);

        kde.setNr(15L);
        kde.setName("Jeany");
        hash.insert(kde);

        std::cout << "\nInsertion complete: " << std::endl;

        hash.display();

        unsigned long key;
        std::cout << "Key? ";
        std::cin >> key;

        HashEntry temp = hash.retrieve(key);
        if(temp.getNr() != 0L){ temp.display(); }
        else{
            std::cout << "Key " << key << " not found" << std::endl;
        }
    }catch(OpenError& err){
        std::cerr << "Error in opening the file: "
            << err.get_name() << std::endl;
        exit(EXIT_FAILURE);
    }catch(WriteError& err){
        std::cerr << "Error writing to file: "
            << err.get_name() << std::endl;
        exit(EXIT_FAILURE);
    }catch(ReadError& err){
        std::cerr << "Error reading from file: "
            << err.get_name() << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
