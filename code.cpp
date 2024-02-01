#include <iostream>
#include <fstream>
#include <string>
#include "utility.cpp"
using namespace std;

//Function prototypes
bool reading();
bool reg(string first);
bool num(string second);

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

//Defining error variable and utility shortcut
string error;
helper h;

// Defining array sizes for register and mem
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

//Function to check if "data.asm" file exists. If not, create a new file
bool reading()
{
    // Check if the file "data.txt" exists
    ifstream check("william-basic-20240201a.asm");
    bool exists = check.good();
    check.close();

    if (!exists)
    {
        h.display("data.asm file not found, new file created");
        ofstream datafile("william-basic-20240201a.asm");
        return false;
    } return true;
}

//Test if parameter is a register
bool reg(string first)
{
    // Test if first operand is a register, else quit the program
    if (!h.isRegister(first, error)) 
    {
        h.display(error);
        exit(1);
    } return true;
}

//Test if parameter is a number
bool num(string second)
{
    // Test if second operand is a number, else quit the program
    if (!h.isNumber(second)) 
    {
        h.display("Compile error: second operand is missing or is not a number.");
        exit(1);
    } return true;
}

int main()
{
    int PC = 0;
    int OF = 0;
    int UF = 0;
    int ZF = 0;
    int CF = 0;

    bool filefound = reading();

    if (filefound)
    {
        // Create a text string, which is used to output the text file
        string line;

        string operation = "";
        string firstOperand = "";
        string secondOperand = "";

        // Read from the text file
        ifstream datafile("william-basic-20240201a.asm");
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
            int firstOperandIndex, secondOperandIndex;
            if (h.hasSquaredBrackets(firstOperand))
                firstOperandIndex = h.charToInt(firstOperand, 2);
            else if (h.isRegister(firstOperand, error))
                firstOperandIndex = h.charToInt(firstOperand, 1);
            else
                firstOperandIndex = 0;

            if (secondOperand != "\0")
            {
                if (h.hasSquaredBrackets(secondOperand))
                    secondOperandIndex = h.charToInt(secondOperand, 2);
                else if (h.isRegister(secondOperand, error))
                    secondOperandIndex = h.charToInt(secondOperand, 1);
                else
                    secondOperandIndex = 0;
            }

            h.display("Operation: " + result[0]);
            h.display("first param: " + result[1]);
            h.display("second param: " + result[2]);
            h.display("-----------");
           
            if (operation == SHIFT_LEFT || operation == SHIFT_RIGHT || operation == ROTATE_LEFT ||
                operation == ROTATE_RIGHT) 
            {
                reg(firstOperand);
                num(secondOperand);

                if (operation == SHIFT_LEFT) 
                    registers[firstOperandIndex] = registers[firstOperandIndex] << stoi(secondOperand);
                else if (operation == SHIFT_RIGHT)
                    registers[firstOperandIndex] = registers[firstOperandIndex] >> stoi(secondOperand);
                else if (operation == ROTATE_LEFT)
                    registers[firstOperandIndex] = (registers[firstOperandIndex] << stoi(secondOperand)) | (registers[firstOperandIndex] >> (INT_BITS - stoi(secondOperand)));
                else if (operation == ROTATE_RIGHT)
                    registers[firstOperandIndex] = (registers[firstOperandIndex] >> stoi(secondOperand)) | (registers[firstOperandIndex] << (INT_BITS - stoi(secondOperand)));
            }
            
            else if (operation == LOAD || operation == STORE) 
            {
                //Check if operand is register
                reg(firstOperand);
                
                int memoryValue;   //Get value to store in registers
                int memoryIndex;

                if (h.hasSquaredBrackets(secondOperand)) // if it is a register
                {
                    memoryIndex = registers[secondOperandIndex];
                    if (h.checkMEMIndex(memoryIndex)) 
                    {
                        cout << "Invalid memory index\n";
                        return 0;
                    }
                    memoryValue = MEM[memoryIndex]; // Obtaining the register value of the second operand
                }
                else if (h.isNumber(secondOperand)) // if it is a memory address
                {
                    memoryIndex = stoi(secondOperand);
                    if (h.checkMEMIndex(memoryIndex)) 
                    {
                        cout << "Invalid memory index\n";
                        return 0;
                    }
                    memoryValue = MEM[memoryIndex]; // Obtaining the memory value of the second operand
                }
                else
                {
                    h.display("Compile error: second operand is not in the format [Rddr]");
                    return 0;
                }

                if (operation == LOAD)
                {
                    cout << "Loading value: " << memoryValue << " into R" << firstOperandIndex << endl << endl;
                    registers[firstOperandIndex] = memoryValue; // storing 
                } 
                else if (operation == STORE)
                {
                    if (h.isNumber(secondOperand))
                        MEM[memoryIndex] = registers[firstOperandIndex];
                    else if (h.hasSquaredBrackets(secondOperand))
                        MEM[registers[secondOperandIndex]] = registers[firstOperandIndex];
                }
            }

            else if  (operation == ADD || operation == SUBTRACT || operation == MULTIPLY || 
                      operation == DIVIDE || operation == INCREMENT || operation == DECREMENT) 
            {
                int outcome;

                //Test if first operand is a register, else quits program
                if (!h.isRegister(firstOperand, error)) 
                {
                    h.display(error);
                    return 0; 
                }

                if (operation == ADD)
                {
                    outcome = registers[firstOperandIndex] + registers[secondOperandIndex];
                    registers[secondOperandIndex] = outcome; // assign the operand 2 the value after arithmetic
                }
                else if (operation == SUBTRACT)
                {
                    outcome = registers[secondOperandIndex] - registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome; // assign the operand 2 the value after arithmetic
                }
                else if (operation == MULTIPLY)
                {
                    outcome = registers[secondOperandIndex] * registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome; // assign the operand 2 the value after arithmetic
                }
                else if (operation == DIVIDE)
                {
                    outcome = registers[secondOperandIndex] / registers[firstOperandIndex];
                    registers[secondOperandIndex] = outcome; // assign the operand 2 the value after arithmetic
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

                if (outcome > 127)
                    OF = 1;
                else if (outcome < -128)
                    UF = 1;
                else if (outcome == 0)
                    ZF = 1;
            }

            else if (operation == INPUT || operation == OUTPUT)
            {
                if (operation == INPUT)
                {
                    int value;
                    cout << "Please input a value to store in R" << firstOperandIndex << endl;
                    cin >> value;

                    registers[firstOperandIndex] = value;
                } 
                else if (operation == OUTPUT)
                    cout << registers[firstOperandIndex] << endl;
            } 

            else if (operation == MOVE)
            {
                if (firstOperand[0] == 'R')
                    registers[secondOperandIndex] = registers[firstOperandIndex];

                else if (h.hasSquaredBrackets(firstOperand)) 
                {
                    int memoryIndex = registers[firstOperandIndex];

                    if (!(memoryIndex > 63 && memoryIndex < 0))
                        registers[secondOperandIndex] = MEM[memoryIndex];
                    else 
                    {
                        h.display("Invalid memory address");
                        return 0;
                    }
                } 
                else
                    registers[secondOperandIndex] = stoi(firstOperand);
            }

            PC += 1;
            cout << "Program Counter: " << PC << endl;
            cout << "OF/UF/CF/ZF: " << OF << ", " << UF << ", " << CF << ", " << ZF << endl << endl;

            for (int &val : registers)
            {
                cout << val << " ";
            }
            cout << endl << endl;
        } 

        for (int i = 0; i < 7; ++i)
        {
            cout << "R" << i << ": " << registers[i] << " ";
        }
        cout << endl;

        h.printMEM(MEM);
    }
    
    return 0;
}