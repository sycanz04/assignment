#include <iostream>
#include <fstream>
#include <string> 
using namespace std;


int main () {
    // Create a text file
    // ofstream MyWriteFile("filename.txt");

    // Write to the file
    // MyWriteFile << "Files can be tricky, but it is fun enough!";
    
    // Close the file
    // MyWriteFile.close();

    // Create a text string, which is used to output the text file
    string line;
    const string move = "MOV";
    const string add = "ADD";
    const string mul = "MUL";
    const string store = "STORE";

    // Read from the text file
    ifstream datafile("data.txt");

    // Use loop to read file line by line
    while (getline (datafile, line)) {
        if (line.find(move) != string::npos) {
            // Execute the corresponding instruction
            cout << "MOV found" << endl;
        }
        else{
            cout << "MOV not found" << endl;
        }
    }

    // Close the file
    datafile.close();
}
