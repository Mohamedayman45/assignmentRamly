//
// Created by User on 10/24/2024.
//


#include "machine.h"
#include <bits/stdc++.h>

MemoryRegisters Registers;
void machine :: load1(int r, string value) {
    Registers.setRegister(r, value);
}
void machine ::load2(int r, string value) {
    Registers.setRegister(r , value);
}

void machine ::store(int r, int xy) {
    cout << "store";
    cout << "r is " << r << endl;
    cout << "xy is " << xy << endl;
}

void machine ::Register1ToRegister2(int register1, int register2) {
    Registers.setRegister(register2, Registers.getRegister(register1));
}

//Put Register 1, 2 in Register 3
//Keep in mind values are stored as string
void machine ::FloatingPointToRegister3(int register1, int register2, int register3){
    ALU Alu;
    vector <string> RegistersInBin;
    vector <string> RegistersInDec;
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register1)));
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register2)));
    Alu.hexToDec(Registers.getRegister(register3)); //To be later used for the addition as a decimal
    cout << "Hex of FP Notation r1: " << Registers.getRegister(register1) << endl;
    cout << "Hex of FP Notation r2: " << Registers.getRegister(register2) << endl;

    for (int i = 0; i < RegistersInBin.size(); ++i) {
        int sign = 0;
        if (RegistersInBin[i][0] != '0') { //Check First Bit 
            sign = 1;
        }
        int bias = 4;
        // Extract Exponent of 3 bits after sign
        int exponentShift = stoi(RegistersInBin[i].substr(1, 3), nullptr, 2) - bias; //Converted A Binary Number (string) to Decimal (int)  
        string mantissa = RegistersInBin[i].substr(4, 4);
        int j = mantissa.size() - 1; //Remove zeroes in the end ex: 1100
        while (j >= 0 && mantissa[j] == '0') {
            j--;
        }
        string BinaryMantissaWithoutZeroes = mantissa.substr(0, j + 1); // ex: 11
        string FinalBinaryRepresentation = string(-exponentShift, '0') + BinaryMantissaWithoutZeroes;
        // cout << "Exponent: " << exponentShift << endl;
        // cout << "mantissa: " << mantissa << endl;
        // cout << "mantissa no zeroes: " << BinaryMantissaWithoutZeroes << endl;
        // cout << "Final Binary (not multiplied by sign): " << FinalBinaryRepresentation << endl;
        // cout << "Decimal Representation (signed) : " << stoi(FinalBinaryRepresentation, nullptr, 2) * pow(-1, sign) << endl;





    }
    // cout << "Binary Value: " << Register1ValueBin << endl;
    // cout << "Binary Value: " << Register2ValueBin << endl;
    // cout << "Binary Value: " << Register3ValueBin << endl; 
}

int machine ::jump(int registerNumber, int memoryAddressOp1, int i) {
    if (Registers.getRegister(registerNumber) == Registers.getRegister(0)){
        return memoryAddressOp1 - 2;
    }
    return i;
}
