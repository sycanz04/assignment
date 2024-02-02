#include <iostream>
#include <fstream>
#include <string>
#include "utility.cpp"
using namespace std;

// Converts operation into readable action
const string INPUT = "IN";
const string OUTPUT = "OUT";
const string MOVE = "MOV";
const string ADD = "ADD";
const string SUBTRACT = "SUB";
const string MULTIPLY = "MUL";
const string DIVIDE = "DIV";
const string INCREMENT = "INC";
const string DECREMENT = "DEC";
const string ROTATE_LEFT = "ROL";
const string ROTATE_RIGHT = "ROR";
const string SHIFT_LEFT = "SHL";
const string SHIFT_RIGHT = "SHR";
const string LOAD = "LOAD";
const string STORE = "STORE";

const int INT_BITS = 8;

// Defining error variable and utility shortcut
string error;
helper h;

// Defining array sizes for register and memory
int registers[7] = {00, 00, 00, 00, 00, 00, 00}; // R0 to R6
int MEM[64] = 
{00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00, 
00, 00, 00, 00, 00, 00, 00, 00};

int main()
{
    int PC = 0;
    int OF = 0;
    int UF = 0;
    int CF = 0;
    int ZF = 0;

    bool filefound = h.reading();

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

            string *result = h.parseLine(line); // Expects an array with 3 values

            if (result == NULL) 
            {
                cout << "Compile error: Invalid line: " + line << endl;
                return 0;
            }

            operation = result[0];
            firstOperand = result[1];
            secondOperand = result[2];

            // Fetching register index
            int firstOperandIndex, secondOperandIndex;
            if (h.hasSquaredBrackets(firstOperand))
                firstOperandIndex = h.charToInt(firstOperand, 2);
            else if (h.isRegister(firstOperand, error))
                firstOperandIndex = h.charToInt(firstOperand, 1);
            else
                firstOperandIndex = 0;

            if (secondOperand != "\0") // If no second operand, skips getting index
            {
                if (h.hasSquaredBrackets(secondOperand))
                    secondOperandIndex = h.charToInt(secondOperand, 2);
                else if (h.isRegister(secondOperand, error))
                    secondOperandIndex = h.charToInt(secondOperand, 1);
                else
                    secondOperandIndex = 0;
            }

            // Prints into console
            h.display("Operation: " + result[0]);
            h.display("First Parameter: " + result[1]);
            h.display("Second Parameter: " + result[2]);
            h.display("-----------");

            // Input and output operations
            if (operation == INPUT || operation == OUTPUT)
            {
                h.reg(firstOperand);

                if (operation == INPUT)
                {
                    int value;
                    cout << "Please input a value to store in R" << firstOperandIndex << endl;
                    cin >> value;
                    cout << endl;

                    registers[firstOperandIndex] = value;
                } 
                else if (operation == OUTPUT)
                    cout << "Value at R" << firstOperandIndex << " is " << registers[firstOperandIndex] << endl << endl;
            } 

            // Move operations
            else if (operation == MOVE)
            {
                if (firstOperand[0] == 'R') // First operand is a register
                    registers[secondOperandIndex] = registers[firstOperandIndex];

                else if (h.hasSquaredBrackets(firstOperand)) // First operand has squared brackets
                {
                    int memoryIndex = registers[firstOperandIndex];

                    if (h.checkMEMIndex(memoryIndex))
                    {
                        h.display("Invalid memory address");
                        return 0;
                    }
                    else 
                        registers[secondOperandIndex] = MEM[memoryIndex];
                } 
                else // First operand is a value
                    registers[secondOperandIndex] = stoi(firstOperand);
            }

            // Arithmetic, increment and decrement operations
            else if  (operation == ADD || operation == SUBTRACT || operation == MULTIPLY || 
                      operation == DIVIDE || operation == INCREMENT || operation == DECREMENT) 
            {
                int outcome;

                h.reg(firstOperand);
                if (secondOperand != "\0") // Check if second operand is register only if second operand exists
                {
                    h.reg(secondOperand);
                }

                if (operation == ADD)
                {
                    outcome = registers[firstOperandIndex] + registers[secondOperandIndex];
                    registers[secondOperandIndex] = outcome;
                }
                else if (operation == SUBTRACT)
                {
                    outcome = registers[secondOperandIndex] - registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome;
                }
                else if (operation == MULTIPLY)
                {
                    outcome = registers[secondOperandIndex] * registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome;
                }
                else if (operation == DIVIDE)
                {
                    outcome = registers[secondOperandIndex] / registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome;
                }
                else if (operation == INCREMENT)
                {
                    outcome = registers[firstOperandIndex] + 1;
                    registers[firstOperandIndex] = outcome;
                }
                else if (operation == DECREMENT)
                {
                    outcome = registers[firstOperandIndex] - 1;
                    registers[firstOperandIndex] = outcome;
                }

                if (outcome > 255)
                {
                    OF = 1; // Overflow flag set to 1
                    CF = 1; // Carry flag set to 1
                }
                else if (outcome < 0)
                    UF = 1; // Underflow flag set to 1
                else if (outcome == 0)
                    ZF = 1; // Zero flag set to 1
            }

            // Rotate and shift operations
            else if (operation == SHIFT_LEFT || operation == SHIFT_RIGHT || operation == ROTATE_LEFT ||
                    operation == ROTATE_RIGHT) 
            {
                h.reg(firstOperand);
                h.num(secondOperand);
                unsigned char outcome;

                if (operation == SHIFT_LEFT) 
                    outcome = registers[firstOperandIndex] << stoi(secondOperand);
                else if (operation == SHIFT_RIGHT)
                    outcome = registers[firstOperandIndex] >> stoi(secondOperand);
                else if (operation == ROTATE_LEFT)
                    outcome = (registers[firstOperandIndex] << stoi(secondOperand)) | (registers[firstOperandIndex] >> (INT_BITS - stoi(secondOperand)));
                else if (operation == ROTATE_RIGHT)
                    outcome = (registers[firstOperandIndex] >> stoi(secondOperand)) | (registers[firstOperandIndex] << (INT_BITS - stoi(secondOperand)));

                registers[firstOperandIndex] = int(outcome);
            }
            
            // Load and store operations
            else if (operation == LOAD || operation == STORE) 
            {
                h.reg(firstOperand);
                
                int memoryValue;
                int memoryIndex;

                if (h.hasSquaredBrackets(secondOperand))
                {
                    memoryIndex = registers[secondOperandIndex];
                    if (h.checkMEMIndex(memoryIndex)) 
                    {
                        cout << "Invalid memory index\n";
                        return 0;
                    }
                    memoryValue = MEM[memoryIndex];
                }
                else if (h.isNumber(secondOperand))
                {
                    memoryIndex = stoi(secondOperand);
                    if (h.checkMEMIndex(memoryIndex)) 
                    {
                        cout << "Invalid memory index\n";
                        return 0;
                    }
                    memoryValue = MEM[memoryIndex];
                }
                else
                {
                    h.display("Compile error: second operand is not in the format [Rddr]");
                    return 0;
                }

                if (operation == LOAD)
                {
                    cout << "Loading value: " << memoryValue << " into R" << firstOperandIndex << endl << endl;
                    registers[firstOperandIndex] = memoryValue; 
                } 
                else if (operation == STORE)
                {
                    if (h.isNumber(secondOperand))
                        MEM[memoryIndex] = registers[firstOperandIndex];
                    else if (h.hasSquaredBrackets(secondOperand))
                        MEM[registers[secondOperandIndex]] = registers[firstOperandIndex];
                }
            }

            PC += 1;
            cout << "Program Counter: " << PC << endl;
            cout << "OF/UF/CF/ZF: " << OF << ", " << UF << ", " << CF << ", " << ZF << "#" << endl;
            for (int i = 0; i < 7; ++i)
            {
                cout << "R" << i << ": " << registers[i] << " ";
            }
            cout << "#" << endl;

            cout << "Memory: " << endl;
            h.printMEM(MEM);
            cout << endl;
        } 
    }
    // Opens a file "output.txt"
    ofstream outputFile("output.txt");

    // Outputs registers into "output.txt"
    outputFile << "Registers: ";
    for (int i = 0; i < sizeof(registers) / sizeof(registers[0]); ++i)
    {
        outputFile << registers[i] << " ";
    }
    outputFile << "#" << endl;

    // Outputs flags into "output.txt"
    outputFile << "Flags: " << OF << " " << UF << " " << CF << " " << ZF << "#" << endl;;

    // Outputs program counter into "output.txt"
    outputFile << "PC: " << PC << endl << endl;

    // Outputs memory into "output.txt"
    outputFile << "Memory: " << endl;
    int k = 0;
    for (int i = 0; i < 8; i ++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            outputFile << setw(5) << MEM[k];
            k++;
        }
        outputFile << endl;
    }
    outputFile << "#";

    // Closes file "output.txt"
    outputFile.close();
    
    return 0;
}