#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

int main () {
    // Get the index from both registers
                int operandIndex1 = h.charToInt(firstOperand, 1);
                int operandIndex2 = h.charToInt(secondOperand, 1);

                // Get the value from the registers through the index 
                int firstOperandValue = registers[operandIndex1];
                int secondOperandValue = registers[operandIndex2];

                if (operation == ADD) {
                    outcome = firstOperandValue + secondOperandValue;
                } else if (operation == SUB) {

                }3
}
