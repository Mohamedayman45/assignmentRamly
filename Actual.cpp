void machine ::FloatingPointToRegister3(int register1, int register2, int register3){
    ALU Alu;
    vector <string> RegistersInBin;
    vector <double> RegistersInDec;
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
        string FinalBinaryRepresentation;
        bool BinaryRepresentationStartsWith1 = false;
        if (exponentShift < 0) {
            FinalBinaryRepresentation = string(-exponentShift, '0') + BinaryMantissaWithoutZeroes;
        }
        else if (exponentShift > 0) {
            FinalBinaryRepresentation = string(exponentShift, '1') + BinaryMantissaWithoutZeroes;
            BinaryRepresentationStartsWith1 = true;
        }
        else {
            //NOT SURE WHAT HAPPENS
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes;
        }
        cout << "Final Binary (not multiplied by sign): " << FinalBinaryRepresentation << endl;
        double decimalSum = 0;
        for (int k = 0; k < FinalBinaryRepresentation.size(); ++k) {
            decimalSum += stoi(FinalBinaryRepresentation.substr(k, 1)) * pow(2, -k - 1);
        }

        // cout << "Exponent: " << exponentShift << endl;
        // cout << "mantissa: " << mantissa << endl;
        // cout << "mantissa no zeroes: " << BinaryMantissaWithoutZeroes << endl;
        cout << "Decimal Representation (signed) : " << decimalSum * pow(-1, sign) << endl;
        RegistersInDec.push_back(decimalSum * pow(-1, sign));
    }

    double Register1PlusRegister2 = RegistersInDec[0] + RegistersInDec[1];
    string saveSignInFp = Register1PlusRegister2 < 0.0 ? "1": "0";
    string BinaryR1PlusR2 = Alu.convertFractionalPartToBinary(Register1PlusRegister2).erase(0, 1); //erasing decimal point
    
    int exponent = 0;
    int ones = 0;
    for (char c: BinaryR1PlusR2) {
        if (c == '1') {
            ones++;
        }
        else if (c == '0') {
            exponent--;
        }
    }


    string FinalMantissa = BinaryR1PlusR2.substr(-exponent, ones) + string(4 - ones, '0');
    bitset<3> binary(exponent + 4); //Convert the exponent to a binary number
    string ConvertToHexa = saveSignInFp + binary.to_string() + FinalMantissa; // concatenating all pieces to be a hexadecimal number
    string Register3Value = Alu.binaryToHex(ConvertToHexa);
    cout << "Binary Representation Of Sum: " << BinaryR1PlusR2 << endl;
    cout << "Final Mantissa: " << FinalMantissa << endl;
    cout << "Final 8 Bit Form: " << ConvertToHexa << endl;
    cout << "Save This in Register: " << Register3Value << endl;
    Registers.setRegister(register3, Register3Value);

}
