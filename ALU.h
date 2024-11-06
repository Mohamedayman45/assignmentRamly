//
// Created by User on 10/28/2024.
//
#include <bits/stdc++.h>

using namespace std;

#ifndef A1_T4_MAIN_ALU_H
#define A1_T4_MAIN_ALU_H

class ALU
{
public:
    void explicitNormalize(const string &binary, int &exponent, string &mantissa);
    int hexToDec(string hex);
    double convertBinaryToDecimal(int sign, int exponentShift, const string &BinaryMantissaWithoutZeroes);
    string HexToBinary(string hex);
    string binaryToHex(const string &binary);
    string doubleToBinaryString(double number);
    string convertTo8BitFloatingPoint(const string &binary, string sign);
};

#endif // A1_T4_MAIN_ALU_H
