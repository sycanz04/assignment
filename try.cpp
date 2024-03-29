#include <iostream>
#include <fstream>
#include <string>
#include "utility.cpp"
using namespace std;

//Function prototypes
bool reading();
bool reg(string first);
bool num(string second);

//Defining targeted strings for reading
const string MOVE = "MOV";
const string ADD = "ADD";
const string MUL = "MUL";
const string SHIFT_LEFT = "SHL";
const string SHIFT_RIGHT = "SHR";
const string ROTATE_LEFT = "ROL";
const string ROTATE_RIGHT = "ROR";
const string LOAD = "LOAD";
const string STORE = "STORE";

const int INT_BITS = 8;

//Defining error variable and utility shortcut
string error;
helper h;

// Defining array sizes for register and mem
int registers[7] = {0, 0, 0, 0, 0, 0, 0}; // R0 to R6
int MEM[64] = 
{0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 4, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0};


//Function to check if "data.asm" file exists. If not, create a new file
bool reading()
{
    // Check if the file "data.txt" exists
    ifstream check("data.asm");
    bool exists = check.good();
    check.close();

    if (!exists)
    {
        h.display("data.asm file not found, new file created");
        ofstream datafile("data.asm");
        return false;
    }

    else
    {
        return true;
    }
}

//Test if parameter is a register
bool reg(string first)
{
    // Test if first operand is a register, else quit the program
    if (!h.isRegister(first, error)) {
        h.display(error);
        exit(1);
    }
}

//Test if parameter is a number
bool num(string second)
{
    // Test if second operand is a number, else quit the program
    if (!h.isNumber(second)) {
        h.display("Compile error: second operand is missing or is not a number.");
        exit(1);
    }
}

int main()
{
    //Declare program counter
    int pc = 0;

    bool filefound = reading();

    if (filefound)
    {
        // Create a text string, which is used to output the text file
        string line;

        string operation = "";
        string firstOperand = "";
        string secondOperand = "";

        // Read from the text file
        ifstream datafile("data.asm");
        // Use loop to read file line by line
        while (getline(datafile, line)) 
        {
            if (line.length() == 0)
                continue;

            string *result = h.parseLine(line); // expects an array with 3 values

            if (result == NULL) 
            {
                cout << "Compile error: Invalid line: " + line << endl;
                return 0;
            }

            operation = result[0];
            firstOperand = result[1];
            secondOperand = result[2];

            int registryIndex = 0;
            int registryValue = 0;

            h.display("Operation: " + result[0]);
            h.display("first param: " + result[1]);
            h.display("second param: " + result[2]);
            h.display("-----------");
            if (operation == SHIFT_LEFT || operation == SHIFT_RIGHT || operation == ROTATE_LEFT ||
                operation == ROTATE_RIGHT) {

                int operand2Int;
                int removedBracketsIndex;

                reg(firstOperand);
                num(secondOperand);

                operand2Int = stoi(secondOperand);              // Converting second operand (shift value) into integer
                registryIndex = h.charToInt(firstOperand, 1);   // Obtaining the index
                registryValue = registers[registryIndex];       // Obtaining the register array value through the index

                char outcome = '\0';

                if (operation == SHIFT_LEFT) {
                    outcome = registryValue << operand2Int;
                } else if (operation == SHIFT_RIGHT) {
                    outcome = registryValue >> operand2Int;
                } else if (operation == ROTATE_LEFT) {
                    outcome = (registryValue << operand2Int) | (registryValue >> (INT_BITS - operand2Int));
                } else if (operation == ROTATE_RIGHT) {
                    outcome = (registryValue >> operand2Int) | (registryValue << (INT_BITS - operand2Int));
                }

                registryValue = outcome; // Assign the character to the integer so that it will show when printing out
                registers[registryIndex] = registryValue; // Store the value back into the register

            }
            
            else if (operation == LOAD || operation == STORE) 
            {
                //Check if operand is register
                reg(firstOperand);

                int new2operand = stoi(secondOperand);   //Get input value to store in registers
                int memoryIndex = 0;

                if (h.isNumber(secondOperand))
                { // if it is a memory address
                    // TODO: check if memory index is out of range(between 0 and 63)
                    int memoryIndex = stoi(secondOperand);
                    new2operand = MEM[memoryIndex];  // Obtaining the memory value of the second operand
                }
                
                else if (h.hasSquaredBrackets(secondOperand))
                { // if it is a register
                    registryIndex = h.charToInt(secondOperand, 2);
                    new2operand = registers[registryIndex];  // Obtaining the register value of the second operand
                }

                else
                {
                    h.display("Compile error: second operand is not in the format [Rddr]");
                    return 0;
                }

                registryIndex = h.charToInt(firstOperand, 1);

                if (operation == LOAD)
                {
                    cout << "Loading value: " << result[2] << " into R" << registryIndex << endl << endl;
                    registers[registryIndex] = stoi(result[2]);
                } 
                else if (operation == STORE)
                {
                    if (h.isNumber(secondOperand))
                    {
                        MEM[stoi(secondOperand)] = registers[registryIndex];
                    }
                    else if (h.hasSquaredBrackets(secondOperand))
                    {
                        memoryIndex = registers[h.charToInt(secondOperand, 2)];
                        if (!(memoryIndex > 64 || memoryIndex < 0))
                            {
                                MEM[memoryIndex] = registers[registryIndex];
                            }
                        else
                        {
                            h.display("Invalid memory address");
                            return 0;
                        }
                    }
                }
            }
            pc += 1;
            cout << "Program Counter: " << pc << endl;;
        } 

        for (int i = 0; i < 7; ++i)
        {
            cout << "R" << i << ": " << registers[i] << " ";
        }
        cout << endl;

    }
    h.printMEM(MEM);

    return 0;
}