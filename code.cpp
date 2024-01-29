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
        const string MOVE = "MOV";
        const string ADD = "ADD";
        const string MUL = "MUL";
        const string SHIFT_LEFT = "SHL";
        const string SHIFT_RIGHT = "SHR";
        const string ROTATE_LEFT = "ROL";
        const string ROTATE_RIGHT = "ROR";
        const string STORE = "STORE";

        // Read from the text file
        ifstream datafile("data.asm");

        int pc = 0;
        // Use loop to read file line by line
        while (getline (datafile, line)) {
            // If found keyword in string, then execute command
            if (line.find(MOVE) != string::npos) {
                cout << "MOV found" << endl;
                pc += 1;
            }
            else if (line.find(ADD) != string::npos) {
                cout << "ADD found" << endl; 
                pc += 1;
            }
            else if (line.find(MUL) != string::npos) {
                cout << "MUL found" << endl;
                pc += 1;
            }
            else if (line.find(SHIFT_LEFT) != string::npos) {
                cout << "MUL found" << endl;
                pc += 1;
            }
            else if (line.find(SHIFT_RIGHT) != string::npos) {
                cout << "MUL found" << endl;
                pc += 1;
            }
             else if (line.find(ROTATE_LEFT) != string::npos) {
                cout << "MUL found" << endl;
                pc += 1;
            }           
            else if (line.find(ROTATE_RIGHT) != string::npos) {
                cout << "MUL found" << endl;
                pc += 1;
            }
            else if (line.find(STORE) != string::npos) {
                cout << "STORE found" << endl;
                pc += 1;
            }
            else {
                cout << "No commands found" << endl;
            }
        }
        cout << "Program Counter: " << pc << endl;
    }
}

int main()
{
    reading();
    MemAndReg();

    return 0;
}