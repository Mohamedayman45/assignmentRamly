//
// Created by User on 10/24/2024.
//


#include "machine.h"
#include "registerr.h"
#include <bits/stdc++.h>
Memory Cell;
MemoryRegisters Registers;
void machine :: load1(int r, string value) {
    Registers.setRegister(r, value);
}
void machine ::load2(int r, string value) {
    Registers.setRegister(r , value);
}
void machine::store(int r, int xy) {
    string value = Registers.getRegister(r);
    if (xy == 0x00) {
        cout << "Output to screen: " << value << endl;
    } else {
        Cell.setCell(xy, value);
        cout << "Stored value " << value << " from register " << r << " to memory address " << hex << xy << endl;
    }
}

void machine ::Register1ToRegister2(int register1, int register2) {
    Registers.setRegister(register2, Registers.getRegister(register1));
}

//Put Register 1, 2 in Register 3
//Keep in mind values are stored as string
void machine ::FloatingPointToRegister3(int register1, int register2, int register3){
    ALU Alu;
    vector <string> RegistersInBin;
    vector <double> RegistersInDec;
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register1)));
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register2)));

    cout << "Hex of FP Notation r1: " << Registers.getRegister(register1) << endl;
    cout << "Hex of FP Notation r2: " << Registers.getRegister(register2) << endl;

    for (int i = 0; i < RegistersInBin.size(); ++i) {
        int sign = (RegistersInBin[i][0] == '1') ? 1 : 0;
        int bias = 4;
        // Extract Exponent of 3 bits after sign
        int exponentShift = stoi(RegistersInBin[i].substr(1, 3), nullptr, 2) - bias; //Converted A Binary Number (string) to Decimal (int)  
        string mantissa = RegistersInBin[i].substr(4, 4);
        size_t j = mantissa.size() - 1; //Remove zeroes in the end ex: 1100
        while (j >= 0 && mantissa[j] == '0') {
            j--;
        }
        string BinaryMantissaWithoutZeroes = mantissa.substr(0, j + 1); // ex: 11
        
        // This cases gives error in part 2 of code! test in the end
        // string BinaryMantissaWithoutZeroes = "1101";
        // exponentShift = 3;

        double decimalSum = Alu.convertBinaryToDecimal(sign, exponentShift, BinaryMantissaWithoutZeroes);;

        cout << "Decimal Representation (signed) : " << decimalSum << endl;
        RegistersInDec.push_back(decimalSum);
    }

    double Register1PlusRegister2 = RegistersInDec[0] + RegistersInDec[1];
    string saveSignInFp = (Register1PlusRegister2) < 0.0 ? "1": "0";
    
    // string BinaryMantissa = ;
    // cout << "binary Final!!!!: " << BinaryMantissa << endl;


    // Convert the biased exponent to a 3-bit binary string
    // bitset<3> exponentBits(biasedExponent);
    // string finalBinaryRepresentation = saveSignInFp + exponentBits.to_string() + BinaryMantissa;
    // cout << "Final 8 Bit Form: " << finalBinaryRepresentation << endl;
    
    // string Register3Value = Alu.binaryToHex(finalBinaryRepresentation); // concatenating all pieces to be a hexadecimal number

    // cout << "Save This in Register: " << Register3Value << endl;
    // Registers.setRegister(register3, Register3Value);

}

int machine ::jump(int registerNumber, int memoryAddressOp1, int i) {
    if (Registers.getRegister(registerNumber) == Registers.getRegister(0)){
        return memoryAddressOp1 - 2;
    }
    return i;
}
string machine::getRegisterValue(int r) {
    return registers.getRegister(r);
}

void machine::add(int r, int s, int t) {

    int valueS = std::stoi(registers.getRegister(s), nullptr, 16);
    int valueT = std::stoi(registers.getRegister(t), nullptr, 16);

    int result = valueS + valueT;
    stringstream ss;
    ss << hex << (result & 0xFFFF);
    registers.setRegister(r, ss.str());

}
