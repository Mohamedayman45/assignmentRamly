//
// Created by User on 10/28/2024.
//
#include <bits/stdc++.h>

using namespace std;

#ifndef A1_T4_MAIN_ALU_H
#define A1_T4_MAIN_ALU_H


class ALU {
    public:
        int hexToDec(string hex);
        string HexToBinary(string hex);
        string convertFractionalPartToBinary(double fractionalPart);
        string binaryToHex(const string& binary);
        string convertDecimalToBinary(double number, int &normalizedExponent);
        double convertBinaryToDecimal(int sign, int exponentShift, const string &BinaryMantissaWithoutZeroes);
        string convertDecimalToFloatingPoint(double decimalNumber);

};



#endif //A1_T4_MAIN_ALU_H
