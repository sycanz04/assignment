#include <iostream>
#include <fstream>
#include <string> 
#include "utility.cpp"
using namespace std;

int main () {



    const string MOVE = "MOV";
    const string ADD = "ADD";
    const string SUB = "SUB";
    const string MUL = "MUL";
    const string DIV = "DIV";
    const string SHIFT_LEFT = "SHL";
    const string SHIFT_RIGHT = "SHR";
    const string ROTATE_LEFT = "ROL";
    const string ROTATE_RIGHT = "ROR";
    const string LOAD = "LOAD";
    const string STORE = "STORE";

    const int INT_BITS = 8;

    int registers[7] = {0, 0, 20, 128, 10, 44, 30}; // R0 to R6
    int MEM[64] = 
    {0, 0, 0, 0, 0, 0, 55, 
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0,}; //MEM[6] = 55
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
           
            if (operation == ADD || operation == SUB || operation == MUL || 
                operation == DIV ) {

                    // Get the index from both registers
                int operandIndex1 = h.charToInt(firstOperand, 1);
                int operandIndex2 = h.charToInt(secondOperand, 1);

                // Get the value from the registers through the index 
                int firstOperandValue = registers[operandIndex1];
                int secondOperandValue = registers[operandIndex2];
                
                if (operation == ADD){
                    ADD = firstOperandValue + secondOperandValue;

                } else if (operation == SUB){
                    SUB = firstOperandValue - secondOperandValue;

                } else if (operation == MUL){
                    MUL = firstOperandValue * secondOperandValue;

                } else if (operation == DIV){
                    DIV = firstOperandValue / secondOperandValue;
                }

                if (!h.isRegister(firstOperand, error)) {
                    h.display(error);
                    return 0;   //DISCUSS
                }

                if (!h.isNumber(secondOperand)) {
                    h.display("Compile error: second operand is missing or is not a number.");
                    return 0;
                }

                int operand2Int = stoi(secondOperand); //value of operand2
                char outcome = '\0';
                if (operation == ADD) {
                    if (!h.isRegister(secondOperand)){      // If the secondOpearation is not a number , then it's register


                    }
                    int registeryValue = registers[h.charToInt(firstOperand, 1)]; // declare registeryValue = R2
                    registeryValue += operand2Int; // 4 + 5
                    cout << registeryValue << "\n-----------" << endl ; // 9
                    } else {//This part is where you add registers = (R2 + R1 = R2)

                    }     
                }
                 
            
        }

    }
}
