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

