void machine::FloatingPointToRegister3(int register1, int register2, int register3) {
    ALU Alu;
    vector<string> RegistersInBin;
    vector<double> RegistersInDec;
    
    // Convert register values to binary
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register1)));
    RegistersInBin.push_back(Alu.HexToBinary(Registers.getRegister(register2)));

    // Print hex values
    cout << "Hex of FP Notation r1: " << Registers.getRegister(register1) << endl;
    cout << "Hex of FP Notation r2: " << Registers.getRegister(register2) << endl;

    // Extract floating-point components and convert to decimal
    for (int i = 0; i < RegistersInBin.size(); ++i) {
        int sign = (RegistersInBin[i][0] == '1') ? 1 : 0;
        int bias = 4;
        int exponent = stoi(RegistersInBin[i].substr(1, 3), nullptr, 2);
        int exponentShift = exponent - bias;
        string mantissa = RegistersInBin[i].substr(4, 4);
        
        // Normalize mantissa: Remove trailing zeroes
        int j = mantissa.size() - 1;
        while (j >= 0 && mantissa[j] == '0') {
            j--;
        }
        string BinaryMantissaWithoutZeroes = mantissa.substr(0, j + 1);
        
        // Construct the full binary representation based on exponent
        string FinalBinaryRepresentation;
        if (exponentShift < 0) {
            FinalBinaryRepresentation = string(-exponentShift, '0') + BinaryMantissaWithoutZeroes;
        } else if (exponentShift > 0) {
            FinalBinaryRepresentation = string(exponentShift, '1') + BinaryMantissaWithoutZeroes;
        } else {
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes;
        }
        
        // Calculate decimal value
        double decimalSum = 0;
        for (int k = 0; k < FinalBinaryRepresentation.size(); ++k) {
            decimalSum += stoi(FinalBinaryRepresentation.substr(k, 1)) * pow(2, -k - 1);
        }
        RegistersInDec.push_back(decimalSum * pow(-1, sign));
    }

    // Perform addition
    double Register1PlusRegister2 = RegistersInDec[0] + RegistersInDec[1];
    string saveSignInFp = (Register1PlusRegister2 < 0.0) ? "1" : "0";
    Register1PlusRegister2 = fabs(Register1PlusRegister2); // Work with the absolute value for normalization

    // Convert to binary representation
    string BinaryR1PlusR2 = Alu.convertFractionalPartToBinary(Register1PlusRegister2).erase(0, 1); // Remove decimal point
    int exponent = 0;

    // Normalize the binary result
    size_t firstOnePos = BinaryR1PlusR2.find('1');
    if (firstOnePos != string::npos) {
        exponent = 4 + firstOnePos; // Adjust exponent based on first '1' position
        BinaryR1PlusR2 = BinaryR1PlusR2.substr(firstOnePos + 1); // Remove leading 1 for mantissa
    }

    // Handle overflow
    if (exponent > 7) {
        exponent = 7;
        BinaryR1PlusR2 = "0000"; // Infinity representation
        cout << "Overflow: Result set to Infinity" << endl;
    }
    // Handle underflow
    else if (exponent < 0) {
        exponent = 0;
        BinaryR1PlusR2 = "0000"; // Zero representation
        cout << "Underflow: Result set to Zero" << endl;
    }

    // Prepare the final mantissa
    string FinalMantissa = BinaryR1PlusR2.substr(0, 4);
    if (FinalMantissa.size() < 4) {
        FinalMantissa += string(4 - FinalMantissa.size(), '0'); // Pad with zeroes if needed
    }

    // Convert exponent to binary
    bitset<3> binaryExponent(exponent);
    string ConvertToHexa = saveSignInFp + binaryExponent.to_string() + FinalMantissa;
    string Register3Value = Alu.binaryToHex(ConvertToHexa);

    // Output the final results
    cout << "Binary Representation Of Sum: " << BinaryR1PlusR2 << endl;
    cout << "Final Mantissa: " << FinalMantissa << endl;
    cout << "Final 8 Bit Form: " << ConvertToHexa << endl;
    cout << "Save This in Register: " << Register3Value << endl;

    Registers.setRegister(register3, Register3Value);
}
