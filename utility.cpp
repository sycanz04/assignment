#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

class helper {

    public:
    string* parseLine(string line) {
        static string result[3]; // 1 = command, 2 = op1, ""3 = op2
        result[0] = "";
        result[1] = "";
        result[2] = "";
        string temp = ""; 
    
        for (auto letter: line) {
                    if (letter == ',' && result[0].length() == 0) return NULL; // invalid line, return empty array 

                    if (letter == '/') 
                        break;

                    if (letter != ' ' && letter != ',') {
                        temp += toupper(letter);
                    } else if (letter == ' ' && temp.length() > 0 ) {
                        if (result[0].length() == 0) {
                            result[0] = temp; // command
                            temp = "";
                        } else if (result[1].length() == 0) {
                            return NULL;
                        }
                    } else if (letter == ',' && temp.length() > 0 && result[1].length() == 0) {
                        result[1] = temp; // op1
                        temp = "";
                    } else if  ((letter == ' ' || letter == ',') && temp.length() > 0 && result[1].length() > 0) 
                        break;
                } 

                if (result[0].length() > 0 && temp.length() > 0) {
                    if (result[1].length() == 0) 
                        result[1] = temp; 
                    else 
                        result[2] = temp;
                }

                if (result[0].length() == 0 || result[1].length() == 0)
                     return NULL; // invalid line, return empty array
                
                return result;
    }

    bool isNumber(string value) {
        int number;

        try {
            number = stoi(value); //try to convert value to number
        }
        catch(exception & e) { // catches the error (if cannot convert, then it is not a number)
            return false;
        } 
        return true;
    }

    bool checkValue (string value, string& error) {     //can use for in, out, add, mul, div but not tested

        if (!isNumber(value)) {
            return false;
        }

        int number = stoi(value); 
        if (number > 127 || number < -128) {
            error = "value out of range";
            return false;
        }
        return true;

    }

    bool isRegister(string value, string &error) {
       
        if (value.length() != 2 || value[0] != 'R' || !isdigit(value[1])) {
            error = "invalid register entry";
            return false;
        }
         
         string indexString(1, value[1]); //creates a string using the value[1] character
         int index = stoi(indexString); //converts the string to an integer
         if (index < 0 || index > 6) {
            error = "Register's index out of range";
            return false;
         }

        return true;    
    }

    void display(string msg) {
        cout << msg << endl;
    }
};