//
// Created by User on 10/28/2024.
//

#include "ALU.h"

int ALU ::hexToDec(string hex)
{
    return stoi(hex, nullptr, 16);
}

string ALU ::HexToBinary(string hex)
{

    // Using bitset to convert the decimal number to binary
    std::bitset<sizeof(int) * CHAR_BIT> binary(hexToDec(hex));

    // Convert to string and return the full binary representation
    return binary.to_string().substr(binary.size() - 8, 8);
}

string ALU ::binaryToHex(const string &binary)
{ // 8Bit
    // Convert binary string to an integer
    bitset<8> bits(binary); // Assuming binary is always 8 bits
    unsigned long decimal = bits.to_ulong();

    // Convert the integer to a hexadecimal string
    stringstream ss;
    ss << hex << uppercase << setw(2) << setfill('0') << decimal; // Formatting to 2 hexadecimal characters

    return ss.str();
}

// Given binary floating-point components (sign, exponentShift, and mantissa), convert to decimal
double ALU::convertBinaryToDecimal(int sign, int exponentShift, const string &BinaryMantissaWithoutZeroes)
{
    string FinalBinaryRepresentation;

    // Adjust the mantissa based on the exponent shift
    if (exponentShift < 0)
    {
        // Add leading zeros to shift the binary point left
        FinalBinaryRepresentation = "0." + string(-exponentShift, '0') + BinaryMantissaWithoutZeroes;
    }
    else if (exponentShift > 0)
    {
        // Insert the binary point at the appropriate position
        if (exponentShift >= BinaryMantissaWithoutZeroes.size())
        {
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes + string(exponentShift - BinaryMantissaWithoutZeroes.size(), '0');
        }
        else
        {
            FinalBinaryRepresentation = BinaryMantissaWithoutZeroes.substr(0, exponentShift) + '.' + BinaryMantissaWithoutZeroes.substr(exponentShift);
        }
    }
    else
    {
        // No shift needed, the binary point is at the start
        FinalBinaryRepresentation = "0." + BinaryMantissaWithoutZeroes;
    }

    // Convert the binary string to a decimal number
    double decimalSum = 0.0;
    bool afterPoint = false;
    int pointPosition = 0;

    for (int k = 0; k < FinalBinaryRepresentation.size(); ++k)
    {
        if (FinalBinaryRepresentation[k] == '.')
        {
            afterPoint = true;
            pointPosition = k;
            continue;
        }

        int bitValue = FinalBinaryRepresentation[k] - '0';
        if (!afterPoint)
        {
            // Bits before the binary point are treated as integer part
            decimalSum = decimalSum * 2 + bitValue;
        }
        else
        {
            // Bits after the binary point contribute as fractional part
            decimalSum += bitValue * pow(2, -(k - pointPosition));
        }
    }

    // Apply the sign bit
    return decimalSum * (sign == 1 ? -1 : 1);
}

string ALU::doubleToBinaryString(double number)
{
    if (number < 0)
    {
        number = -number; // Take the absolute value if the number is negative
    }

    if (number == 0.0)
        return "0.0";

    std::string binary;

    // Convert integer part
    int integerPart = static_cast<int>(number);
    double fractionalPart = number - integerPart;

    // Convert integer part to binary
    std::string integerBinary;
    if (integerPart == 0)
    {
        integerBinary = "0";
    }
    else
    {
        while (integerPart > 0)
        {
            integerBinary = (integerPart % 2 ? "1" : "0") + integerBinary;
            integerPart /= 2;
        }
    }

    binary += integerBinary + ".";

    // Convert fractional part to binary
    int maxFractionBits = 32; // Limit to 32 bits to avoid infinite loop
    while (fractionalPart > 0 && maxFractionBits--)
    {
        fractionalPart *= 2;
        if (fractionalPart >= 1)
        {
            binary += "1";
            fractionalPart -= 1;
        }
        else
        {
            binary += "0";
        }
    }

    return binary;
}

void ALU::explicitNormalize(const string &binary, int &exponent, string &mantissa)
{
    size_t pointPos = binary.find('.');
    string normalizedBinary = binary;
    normalizedBinary.erase(pointPos, 1); // Remove the binary point

    // Find the first '1' in the string to normalize
    size_t firstOne = normalizedBinary.find('1');

    if (firstOne != string::npos)
    {
        // Calculate the exponent based on the position of the first '1'
        if (firstOne < pointPos)
        {
            exponent = pointPos - firstOne;
        }
        else
        {
            exponent = -(firstOne - pointPos);
        }

        // Construct the normalized mantissa
        mantissa = normalizedBinary.substr(firstOne, 4); // Extract the first 4 bits of the mantissa

        // Pad the mantissa with zeroes if it's shorter than 4 bits
        while (mantissa.size() < 4)
        {
            mantissa += '0';
        }
    }
    else
    {
        // If there are no '1's, the number is zero
        exponent = 0;
        mantissa = "0000";
    }
}

// Function to convert to 8-bit floating-point representation
string ALU::convertTo8BitFloatingPoint(const string &binary, string sign)
{
    int exponent;
    string mantissa;

    // Step 1: Explicitly normalize the binary number
    explicitNormalize(binary, exponent, mantissa);

    // Step 2: Apply the bias (bias = 4 for 3-bit exponent)
    int biasedExponent = exponent + 4;

    // Check if the biased exponent is within the 3-bit range
    if (biasedExponent < 0 || biasedExponent > 7)
    {
        // overflow / underflow
        //  IN THIS CASE WE SET THE EXPONENT TO 7 AND MANTISSA TO 0000,
        biasedExponent = 7;
        mantissa = "0000";
    }

    // Step 3: Construct the 8-bit representation
    bitset<3> exponentBits(biasedExponent);
    string finalRepresentation = sign + exponentBits.to_string() + mantissa;

    return finalRepresentation;
}
