#include <iostream>
#include <fstream>
#include <string> 
#include "utility.cpp"
#include <map>
using namespace std;

int main () {



    const string move = "MOV";
    const string add = "ADD";
    const string mul = "MUL";
    const string shiftLeft = "SHL";
    const string shiftRight = "SHR";
    const string rotateLeft = "ROL";
    const string rotateRight = "ROR";
    const string store = "STORE";

/*    std::map<char[2], int> register = {
        { "R0", 0 },
        { "R1", 128 },
        { "R2", 0 },
        { "R3", 0 },
        { "R4", 0 },
        { "R5", 0 },
        { "R6", 0 },
        { "R7", 0 }
    };

*/
    int registers[7] = {0, 5, 0, 0, 0, 0, 0}; // R0 to R7
    string error;
    

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
        helper h;

        string operation = "";
        string firstOperand  = "";
        string secondOperand = "";

        // Read from the text file
        ifstream datafile("data.asm");
        // Use loop to read file line by line
        while (getline (datafile, line)) {

            if (line.length() == 0) continue;

            string* result = h.parseLine(line);

            if (result == NULL ) {
                cout<<"Compile error: Invalid line: "+line<<endl;
                return 0;
            }  

            string operation = result[0];
            string firstOperand  = result[1];
            string secondOperand = result[2];


            h.display("Operation: " + result[0]);
            h.display("first param: " + result[1]);
            h.display("send param: " + result[2]);
            h.display("-----------");



            char firstValue;
            int secondValue = 0;
            char cResult;
           
            if (operation == shiftLeft) {
                h.display("testing");

                if (!h.isRegister(firstOperand, error)) {
                    h.display(error);
                    return 0;
                }

                string registerIndexString(1, firstOperand[1]);
                
                firstValue = registers[stoi(registerIndexString)];
                
                if (!h.isNumber(secondOperand)) {
                    h.display(error);
                    return 0;
                }

                secondValue = stoi(secondOperand);
                cResult = firstValue << secondValue; //
                cout<<cResult<<endl;


                //int registerValue = registers[stoi(firstOperand, nullptr, 0)];
                // TODO: validate shift number
                //registerValue = registerValue>>stoi(result[2], nullptr, 0);

                //std::cout<<registerValue<<"\n";
            }

            //int binaryValue = 128;
            //binaryValue = binaryValue>>1;

            //std::string binary = std::bitset<8>(128).to_string(); //to binary
            //binary = binary>>1;
            //std::cout<<binaryValue<<"\n";
        }
    }

} 


/*
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
            } */
