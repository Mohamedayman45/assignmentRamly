//
// Created by User on 10/28/2024.
//

#include "ALU.h"

int ALU ::hexToDec(string hex) {
    return stoi(hex, nullptr, 16);
}

string ALU ::HexToBinary(string hex) {

    // Using bitset to convert the decimal number to binary
    std::bitset<sizeof(int) * CHAR_BIT> binary(hexToDec(hex));
    
    // Convert to string and return the full binary representation
    return binary.to_string().substr(binary.size() - 8, 8);
}

string ALU ::binaryToHex(const string& binary) { //8Bit
    // Convert binary string to an integer
    bitset<8> bits(binary); // Assuming binary is always 8 bits
    unsigned long decimal = bits.to_ulong();

    // Convert the integer to a hexadecimal string
    stringstream ss;
    ss << hex << uppercase << setw(2) << setfill('0') << decimal; // Formatting to 2 hexadecimal characters

    return ss.str();
}

string ALU ::convertFractionalPartToBinary(double fractionalPart) {
    string binary = ".";
    int precision = 10; // Number of binary digits after the decimal point

    while (precision-- > 0 && fractionalPart > 0.0) {
        fractionalPart *= 2;
        if (fractionalPart >= 1.0) {
            binary += "1";
            fractionalPart -= 1.0;
        } else {
            binary += "0";
        }
    }
    return binary;
}

string ALU::convertDecimalToBinary(double decimalNumber, int &normalizedExponent) {
    string binaryResult;
    normalizedExponent = 0;

    // Handle the integer part first
    int integerPart = static_cast<int>(decimalNumber);
    double fractionalPart = decimalNumber - integerPart;

    // Convert the integer part to binary
    if (integerPart > 0) {
        while (integerPart > 0) {
            binaryResult = to_string(integerPart % 2) + binaryResult;
            integerPart /= 2;
        }
    } else {
        binaryResult = "0"; // If integer part is zero
    }

    // Convert the fractional part to binary
    string fractionalBinary;
    int fractionalBits = 0;
    while (fractionalPart > 0 && fractionalBits < 10) { // Limiting to 10 bits for precision
        fractionalPart *= 2;
        int bit = static_cast<int>(fractionalPart);
        fractionalBinary += to_string(bit);
        fractionalPart -= bit;
        fractionalBits++;
    }

    // Combine integer and fractional parts
    if (fractionalBinary.empty()) {
        binaryResult += ".0"; // No fractional part, just append .0
    } else {
        binaryResult += "." + fractionalBinary;
    }

    // Normalize the mantissa to fit a 4-bit representation
    size_t firstOnePos = binaryResult.find('1');
    if (firstOnePos != string::npos) {
        // Adjust the exponent based on the position of the first '1'
        if (firstOnePos < binaryResult.find('.')) {
            // The '1' is in the integer part
            normalizedExponent = static_cast<int>(binaryResult.find('.') - firstOnePos - 1);
            binaryResult = binaryResult.substr(firstOnePos + 1); // Remove leading '1'
        } else {
            // The '1' is in the fractional part
            normalizedExponent = -static_cast<int>(firstOnePos - binaryResult.find('.') + 1);
            binaryResult = binaryResult.substr(firstOnePos + 1); // Remove leading '1'
        }
    }

    // Trim or pad the mantissa to fit exactly 4 bits
    if (binaryResult.size() < 4) {
        binaryResult += string(4 - binaryResult.size(), '0'); // Pad with zeros
    } else if (binaryResult.size() > 4) {
        binaryResult = binaryResult.substr(0, 4); // Trim to 4 bits
    }

    return binaryResult;
}



// Given binary floating-point components (sign, exponentShift, and mantissa), convert to decimal
double ALU::convertBinaryToDecimal(int sign, int exponentShift, const string &BinaryMantissaWithoutZeroes) {
    string FinalBinaryRepresentation;
    
    // Adjust the mantissa based on the exponent shift
    if (exponentShift < 0) {
        // Add leading zeros to shift the binary point left
        FinalBinaryRepresentation = "0." + string(-exponentShift, '0') + BinaryMantissaWithoutZeroes;
    } else if (exponentShift > 0) {
        // Insert the binary point at the appropriate position
        if (exponentShift >= BinaryMantissaWithoutZeroes.size()) {
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes + string(exponentShift - BinaryMantissaWithoutZeroes.size(), '0');
        } else {
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes.substr(0, exponentShift) + '.' + BinaryMantissaWithoutZeroes.substr(exponentShift);
        }
    } else {
        // No shift needed, the binary point is at the start
        FinalBinaryRepresentation = "0." + BinaryMantissaWithoutZeroes;
    }

    cout << "Final Binary Representation: " << FinalBinaryRepresentation << endl;

    // Convert the binary string to a decimal number
    double decimalSum = 0.0;
    bool afterPoint = false;
    int pointPosition = 0;

    for (int k = 0; k < FinalBinaryRepresentation.size(); ++k) {
        if (FinalBinaryRepresentation[k] == '.') {
            afterPoint = true;
            pointPosition = k;
            continue;
        }
        
        int bitValue = FinalBinaryRepresentation[k] - '0';
        if (!afterPoint) {
            // Bits before the binary point are treated as integer part
            decimalSum = decimalSum * 2 + bitValue;
        } else {
            // Bits after the binary point contribute as fractional part
            decimalSum += bitValue * pow(2, -(k - pointPosition));
        }
    }

    // Apply the sign bit
    return decimalSum * (sign == 1 ? -1 : 1);
}


string ALU::convertDecimalToFloatingPoint(double decimalNumber) {
    // Handling sign
    int sign = decimalNumber < 0 ? 1 : 0;
    if (sign) {
        decimalNumber = -decimalNumber; // Work with positive for conversion
    }

    // Step 1: Convert to binary representation
    // Handle the integer part first (if any)
    string integerPartBinary = "";
    int integerPart = static_cast<int>(decimalNumber);
    
    while (integerPart > 0) {
        integerPartBinary = to_string(integerPart % 2) + integerPartBinary;
        integerPart /= 2;
    }
    
    // Step 2: Convert the fractional part to binary
    string fractionalPartBinary = "";
    double fractionalPart = decimalNumber - static_cast<int>(decimalNumber);
    
    while (fractionalPart > 0 && fractionalPartBinary.length() < 4) { // Limit length for mantissa
        fractionalPart *= 2;
        if (fractionalPart >= 1) {
            fractionalPartBinary += '1';
            fractionalPart -= 1;
        } else {
            fractionalPartBinary += '0';
        }
    }

    // Combine both parts
    string finalBinary = integerPartBinary.empty() ? "0." + fractionalPartBinary : integerPartBinary + "." + fractionalPartBinary;

    // Normalize
    size_t firstOnePos = finalBinary.find('1');
    int exponent = 0;
    
    if (firstOnePos != string::npos) {
        exponent = static_cast<int>(finalBinary.find('.') - firstOnePos - 1);
        finalBinary = finalBinary.substr(firstOnePos + 1); // Remove leading 1 for mantissa
    } else {
        // All zeros, return early
        finalBinary = "0000"; // All zero mantissa if needed
        exponent = -4; // Will require adjustment
    }

    // Adjust exponent with bias
    int biasedExponent = exponent + 4; // Assuming bias of 4
    if (biasedExponent < 0 || biasedExponent > 7) {
        throw std::runtime_error("Exponent out of range for 3-bit representation!");
    }

    // Convert to binary strings
    bitset<3> exponentBits(biasedExponent);
    string mantissa = finalBinary.substr(0, 4); // Get the first 4 bits for mantissa
    while (mantissa.length() < 4) {
        mantissa += '0'; // Pad with zero if necessary
    }
    if (mantissa.length() > 4) {
        mantissa = mantissa.substr(0, 4); // Truncate to 4 bits
    }

    // Create the final floating-point binary representation
    string floatingPointBinary = to_string(sign) + exponentBits.to_string() + mantissa;

    return floatingPointBinary; // This will be the final binary representation
}
