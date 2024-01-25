#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

class helper {

    public:
    string * parseLine(string line) {
        static string result[3]; // 1 = command, 2 = op1, 3 = op2
        string parameter = "";
        string temp = "";
    
        for (auto letter : line) {
            if (letter == ',' && result[0].length() == 0) return NULL; // invalid line, return empty array 

            if (letter == '/') break;

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
            } else if  ((letter == ' ' || letter == ',') && temp.length() > 0 && result[1].length() > 0) break;
        } 

        if (result[0].length() > 0 && temp.length() > 0) {
            if (result[1].length() == 0) result[1] = temp; else result[2] = temp;
        }

        if (result[0].length() == 0 || result[1].length() == 0) return NULL; // invalid line, return empty array
         
        return result;
    }

    bool isNumber(string value) {

        int number;
        try{
            number = stoi(value); 
        }
        catch(std::exception& e) {
            return false;
        } 
        return true;
    }

    bool checkValue (string value, string& error) {

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

    bool isRegister(std::string value, string& error) {
       
        if (value.length() != 2 || value[0] != 'R' || !isdigit(value[1])) {
            error = "invalid register entry";
            return false;
        }
         
         string indexString(1, value[1]);
         int index = stoi(indexString);
         if (index < 0 or index > 7) {
            error = "Register's index out of range";
         }

        return true;    
    }

    void display(string msg) {
        cout << msg << endl;
    }
};