#include <iostream>
#include <fstream>
#include <string> 
#include <iomanip>
using namespace std;

//Memory and register sizes
const int MEM_SIZE = 8;
const int REG_SIZE = 8;

//Initialising 2D and 1D array for memory and registers respectively
int memory[MEM_SIZE] = {0}; // Initializing memory with zeros
int registers[REG_SIZE] = {0}; // Initializing registers with zeros

//Function prototypes
void reading();
void MemAndReg();

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
            cout << setw(4) << memory[i] << " ";
        }
        cout << endl;
    }
}


//Read file function
void reading(){
    // Check if the file "data.txt" exists
    ifstream check("data.asm");
    bool exists = check.good();
    check.close();

    // If it doesn't exists, create a new text file
    if (!exists){
        ofstream datafile("data.asm");
    }

    else{
        // Create a text string, which is used to output the text file
        string line;
        const string move = "MOV";
        const string add = "ADD";
        const string mul = "MUL";
        const string store = "STORE";

        // Read from the text file
        ifstream datafile("data.asm");

        // Use loop to read file line by line
        while (getline (datafile, line)) {
            // If found keyword in string, then execute command
            if (line.find(move) != string::npos) {
                cout << "MOV found" << endl;
            }
            else if (line.find(add) != string::npos) {
                cout << "ADD found" << endl;
            }
            else if (line.find(mul) != string::npos) {
                cout << "MUL found" << endl;
            }
            else if (line.find(store) != string::npos) {
                cout << "STORE found" << endl;
            }
            else {
                cout << "No commands found" << endl;
            }
        }
    }
}

int main()
{
    reading();
    MemAndReg();

    return 0;
}