#include <iostream>
#include <iomanip>
using namespace std;

const int MEM_SIZE = 8;
const int REG_SIZE = 8;

int memory[MEM_SIZE][MEM_SIZE] = {0}; // Initializing memory with zeros
int registers[REG_SIZE] = {0}; // Initializing registers with zeros

void MemAndReg() {

    // Print Registers
    cout << "Registers:" << endl;
    for (int i = 0; i < REG_SIZE; ++i) {
        cout << "R" << i << ": " << setw(4) << registers[i] << "   ";
    }
    cout << endl << endl;

        // Print Memory
    cout << "Memory:" << endl;
    for (int i = 0; i < MEM_SIZE; ++i) {
        for (int j = 0; j < MEM_SIZE; ++j) {
            cout << setw(4) << memory[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    // Example: Load values into memory and registers
    memory[0][0] = 10;
    memory[1][1] = 20;
    registers[0] = 5;
    registers[1] = 15;

    // Print initial state
    MemAndReg();

    return 0;
}
