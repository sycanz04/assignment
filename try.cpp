#include <iostream>
#include <iomanip>

const int MEMORY_SIZE = 8;
const int REGISTER_SIZE = 8;

int memory[MEMORY_SIZE][MEMORY_SIZE] = {0}; // Initializing memory with zeros
int registers[REGISTER_SIZE] = {0}; // Initializing registers with zeros

void printMemoryAndRegisters() {
    // Print Memory
    std::cout << "Memory:" << std::endl;
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        for (int j = 0; j < MEMORY_SIZE; ++j) {
            std::cout << std::setw(4) << memory[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Print Registers
    std::cout << "Registers:" << std::endl;
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        std::cout << "R" << i << ": " << std::setw(4) << registers[i] << "   ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    // Example: Load values into memory and registers
    memory[0][0] = 10;
    memory[1][1] = 20;
    registers[0] = 5;
    registers[1] = 15;

    // Print initial state
    printMemoryAndRegisters();

    cout << "Hello world!" << endl;

    // Your code to read and execute ASM instructions goes here
    // Update the memory and registers accordingly

    // Print final state
    printMemoryAndRegisters();

    return 0;
}