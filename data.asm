.global _start
_start:

    MOV R1, #5  // Load value 5 into register R1
    ADD R1, R1, #6  // Add 6 to the value in R1
    MOV R3, R1  //Copy the value from R1 to R3
    MUL R3, R3, #2  //Multiply the value in R3 by 4 (left shift by 2)
    STR R3, [R0, #20]  //Store the result at memory address 20
    STR R1, [R0, #14]  //Store the original value at memory address 14