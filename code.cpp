#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

int main () {
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
        const string move = "MOV";
        const string add = "ADD";
        const string mul = "MUL";
        const string store = "STORE";

        // Read from the text file
        ifstream datafile("data.asm");

        // Use loop to read file line by line
        while (getline (datafile, line)) {
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
            }
        }
    }
}
