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
    const string STORE = "STORE";

    const int INT_BITS = 8;

    int registers[7] = {0, 122, 0, 0, 0, 0, 0}; // R0 to R6
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
                return 0;   //DISCUSS
            }  

            string operation = result[0];
            string firstOperand  = result[1];
            string secondOperand = result[2];


            h.display("Operation: " + result[0]);
            h.display("first param: " + result[1]);
            h.display("send param: " + result[2]);
            h.display("-----------");


            int secondValue = 0;
           
            if (operation == SHIFT_LEFT || operation == SHIFT_RIGHT || operation == ROTATE_LEFT || operation == ROTATE_RIGHT) {

                if (!h.isRegister(firstOperand, error)) {
                    h.display(error);
                    return 0;   //DISCUSS
                }

                // Getting the value from the register, converting the character to an integer
                string registeryIndexString(1, firstOperand[1]);
                int registeryIndex = stoi(registeryIndexString);
                int registeryValue = registers[registeryIndex];

                if (!h.isNumber(secondOperand)) {
                    h.display("Compile error: second operand is missing or is not a number.");
                    return 0;
                }

                int shiftNumber = stoi(secondOperand);
                char outcome;
                if (operation == SHIFT_LEFT) {
                    outcome = registeryValue << shiftNumber;
                }
                else if (operation == SHIFT_RIGHT) {
                    outcome = registeryValue >> shiftNumber;
                } else if (operation == ROTATE_LEFT) {
                    outcome = (registeryValue << shiftNumber) | (registeryValue >> (INT_BITS - shiftNumber)); 

                } else if (operation == ROTATE_RIGHT) {
                    outcome = (registeryValue >> shiftNumber)|(registeryValue << (INT_BITS - shiftNumber)); 
                }
                registeryValue = outcome; //assign the character to the intger so that it will show when printing out
                cout << registeryValue << endl;
                registers[registeryIndex] = registeryValue;

                continue;
            
            }

        }
    }

} 

