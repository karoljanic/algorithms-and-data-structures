#include "Fifo.hpp"
#include "Lifo.hpp"

#include <iostream>


int main(int argc, char** argv) {
    if(argc != 2) {
        return 0;
    }

    int samplesNumber = std::stoi(argv[1]);

    std::cout << "FIFO:\n";
    Fifo<int> fifo;

    std::cout << "Dodawanie:\n";
    for(int i = 0; i < samplesNumber; i++) {
        std::cout << i << std::endl;
        fifo.push(i);
    }
    std::cout << std::endl;

    std::cout << "Po dodaniu: " << fifo << std::endl << std::endl;

    std::cout << "Zdejmowanie:\n";
    for(int i = 0; i < samplesNumber + 1; i++) {
        try {
            std::cout << fifo.front() << std::endl;
            fifo.pop();
        }
        catch(const std::runtime_error& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Po zdejmowaniu: " << fifo << std::endl << std::endl;

    std::cout << "LIFO:\n";
    Lifo<int> lifo;

    std::cout << "Dodawanie:\n";
    for(int i = 0; i < samplesNumber; i++) {
        std::cout << i << std::endl;
        lifo.push(i);
    }
    std::cout << std::endl;

    std::cout << "Po dodaniu: " << lifo << std::endl << std::endl;

    std::cout << "Zdejmowanie:\n";
    for(int i = 0; i < samplesNumber + 1; i++) {
        try {
            std::cout << lifo.top() << std::endl;
            lifo.pop();
        }
        catch(const std::runtime_error& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Po zdejmowaniu: " << lifo << std::endl << std::endl;

    return 0;
}