#include <iostream>
#include <fstream>
#include <string> 
#include "utility.cpp"
using namespace std;

int main () {



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

    int registers[7] = {0, 0, 0, 0, 0, 0, 0}; // R0 to R6
    int MEM[64] = 
    {0, 0, 0, 0, 0, 0, 0, 
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,};
    string error;
    helper h;
    

    // Check if the file "data.txt" exists
    ifstream check("data.asm");
    bool exists = check.good();
    check.close();

    // If it doesn't exists, create a new text file
    if (!exists){
        h.display("data.asm file not found, new file created");
        ofstream datafile("data.asm");
    }

    else{
        // Create a text string, which is used to output the text file
        string line;

        string operation = "";
        string firstOperand  = "";
        string secondOperand = "";

        // Read from the text file
        ifstream datafile("data.asm");
        // Use loop to read file line by line
        while (getline (datafile, line)) {

            if (line.length() == 0) 
                continue;

            string * result = h.parseLine(line); //expects an array with 3 values

            if (result == NULL ) {
                cout<<"Compile error: Invalid line: "+line<<endl;
                return 0;
            }  

            string operation = result[0];
            string firstOperand  = result[1]; 
            string secondOperand = result[2];

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

                //Test if first operand is a register, else quits program
                if (!h.isRegister(firstOperand, error)) {
                    h.display(error);
                    return 0;  
                }

                //Test if second operand is a number, else quits program
                if (!h.isNumber(secondOperand)) {
                    h.display("Compile error: second operand is missing or is not a number.");
                    return 0;
                }

                operand2Int = stoi(secondOperand);              //Converting second operand (shift value) into integer
                registryIndex = h.charToInt(firstOperand, 1);   //Obtaining the index
                registryValue = registers[registryIndex];       //Obtaining the register array value through the index

                char outcome = '\0';

                if (operation == SHIFT_LEFT) {
                    outcome = registryValue << operand2Int;
                }
                else if (operation  == SHIFT_RIGHT) {
                    outcome = registryValue >> operand2Int;

                } else if (operation == ROTATE_LEFT) {
                    outcome = (registryValue << operand2Int) || (registryValue >> (INT_BITS - operand2Int)); 

                } else if (operation == ROTATE_RIGHT) {
                    outcome = (registryValue >> operand2Int) || (registryValue << (INT_BITS - operand2Int)); 

                }

                registryValue = outcome; //Assign the character to the integer so that it will show when printing out
                registers[registryIndex] = registryValue; //Store the value back into register

            } else if (operation == LOAD || operation == STORE) {

                //Test if first operand is a register, else quits program
                if (!h.isRegister(firstOperand, error)) {
                    h.display(error);
                    return 0; 
                }

                int secondOperandValue = 0;
                int memoryIndex = 0;
                if (h.isNumber(secondOperand)) { //if it is memory address
                    // TODO: check if memory index is out of range(between 0 and 63)
                    int memoryIndex = stoi(secondOperand);
                    secondOperandValue = MEM[memoryIndex];  //Obtaining the memory value of the second operand
                } else if (h.hasSquaredBrackets(secondOperand)) { //if it is register
                    registryIndex = h.charToInt(secondOperand, 2);
                    secondOperandValue = registers[registryIndex];  //Obtaining the register value of the second operand
                } else {
                    h.display("Compile error: second operand is not in the format [Rddr]");
                    return 0;                
                }

                registryIndex = h.charToInt(firstOperand, 1);

                if (operation == LOAD) {
                    registers[registryIndex] = secondOperandValue;
                } else if (operation == STORE) {
                    if (h.isNumber(secondOperand))
                        MEM[stoi(secondOperand)] = registers[registryIndex]; 
                    else if (h.hasSquaredBrackets(secondOperand))
                        registers[h.charToInt(secondOperand, 2)] = registers[registryIndex];
                }
            }

        }
    }

} 

