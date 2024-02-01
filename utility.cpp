#include <iostream>
#include <iomanip>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

class helper {

    public:
    // Separates line into an array of three different results
    string* parseLine(string line) 
    {
        static string result[3]; // 0 = Operation, 1 = First operand, 2 = Second operand
        result[0] = "";
        result[1] = "";
        result[2] = "";
        string temp = ""; 
    
        for (auto letter : line) 
        {
            if (letter == ',' && result[0].length() == 0) 
                return NULL; // Invalid line, return empty array 

            if (letter == ';')
                break;

            if (letter != ' ' && letter != ',')
                temp += toupper(letter);

            else if (letter == ' ' && temp.length() > 0 ) 
            {
                if (result[0].length() == 0) 
                {
                    result[0] = temp; // Operation
                    temp = "";
                }
                else if (result[1].length() == 0)
                    return NULL;
            } 

            else if (letter == ',' && temp.length() > 0 && result[1].length() == 0) 
            {
                result[1] = temp; // First operand
                temp = "";
            } 
            else if  ((letter == ' ' || letter == ',') && temp.length() > 0 && result[1].length() > 0) 
                break;
        } 

        if (result[0].length() > 0 && temp.length() > 0) 
        {
            if (result[1].length() == 0) 
                result[1] = temp; 
            else 
                result[2] = temp; // Second operand
        }

        if (result[0].length() == 0 || result[1].length() == 0)
            return NULL; // Invalid line, return empty array
        
        return result;
    }
    
    // Prints message
    void display(string msg) 
    {
        cout << msg << endl;
    }
    
    // Converts register index into integer
    int charToInt(string operand, int index) 
    {
        string registerIndexString(1, operand[index]); // Convert a char that was pulled from a string into a string
        int registerIndex = stoi(registerIndexString); // Convert the string to an integer
        return registerIndex;
    }

    // Check if value is a number
    bool isNumber(string value)
    {
        int number;

        try // Try to convert value to number
        {
            number = stoi(value); 
        }
        catch(exception & e) // Catches the error (if cannot convert, then it is not a number)
        { 
            return false;
        } 
        
        return true;
    }

    // Check if value is a register
    bool isRegister(string value, string &error) 
    {
        if (value.length() != 2 || value[0] != 'R' || !isdigit(value[1])) 
        {
            error = "Invalid register entry";
            return false;
        }
        
        int index = charToInt(value, 1);

        if (index < 0 || index > 7) 
        {
            error = "Register's index out of range";
            return false;
        }

        return true;    
    }

    // Check if operand has square brackets
    bool hasSquaredBrackets (string operand) 
    {
        if (operand[0] == '[') 
        {
            return true;
        } return false;
    }
    
    // Check if memory index is within range of MEM
    bool checkMEMIndex(int memoryIndex)
    {
        if (memoryIndex > 63 || memoryIndex < 0)
            return true;
        else 
            return false;
    }

    // Prints memory
    void printMEM(int * array) 
    {
        int index = 0;
        for (int i = 0; i < 8; i ++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                cout << setw(5) << array[index];
                index ++;
            } 
            cout << endl;
        }
    }

    // Function to check if "data.asm" file exists. If not, create a new file
    bool reading()
    {
        // Check if the file "data.asm" exists
        ifstream check("data.asm");
        bool exists = check.good();
        check.close();

        if (!exists)
        {
            display("data.asm file not found, new file created");
            ofstream datafile("data.asm");
            return false;
        } return true;
    }

    // Simplified isRegister()
    bool reg(string first)
    {
        string error;
        // Test if first operand is a register, else quit the program
        if (!isRegister(first, error)) 
        {
            display(error);
            exit(1);
        } return true;
    }

    // Simplified isNumber()
    bool num(string second)
    {
        // Test if second operand is a number, else quit the program
        if (!isNumber(second)) 
        {
            display("Compile error: second operand is missing or is not a number.");
            exit(1);
        } return true;
    }
};
