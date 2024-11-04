//
// Created by User on 10/24/2024.
//
#include "memory.h"


Memory::Memory() : Instructions(256, "00") {}; 


vector<string> Memory::ReadToVector(string name) {
    ifstream instructionsFile(name);
    if (!instructionsFile.is_open()) {
        cerr << "Error: Could not open Instructions File." << endl;
        return Instructions;
    }

    string line;
    int index = 0; // Index to keep track of where to overwrite

    while (getline(instructionsFile, line)) {
        string word;
        stringstream ss(line);

        while (ss >> word && index < 256) {
            if (!isValidInstruction(word)) { // Now valid since it's static
                cout << "Invalid Instruction Ignored: " << word << endl; // Print ignored instruction
                continue; // Skip to the next word
            }

            // Add first two characters
            Instructions[index++] = word.substr(0, 2); 
            if (index < 256) {
                Instructions[index++] = word.substr(2, 2); // Add next two characters
            }
        }
    }

    for (int i = 0; i < Instructions.size(); i += 2) {
        if (Instructions[i] == "00") { // To not print initialized 00s
            break;
        }
        cout << Instructions[i] << Instructions[i + 1] << endl;
    }

    instructionsFile.close();
    return Instructions;
}


bool Memory::isValidHexCharacter(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

bool Memory::isValidInstruction(const string& word) {
    if (word.length() != 4) {
        return false; // We expect a fixed length of 4 characters
    }
    
    // Check the first character
    char firstChar = tolower(word[0]);
    if (!(firstChar >= '0' && firstChar <= '6') && firstChar != 'b' && firstChar != 'c') {
        return false; // Invalid first character
    }

    // Check the remaining three characters
    for (size_t i = 1; i < word.length(); ++i) {
        if (!isValidHexCharacter(word[i])) {
            return false; // Invalid character found
        }
    }

    return true; // All checks passed
}

void Memory::setCell(int address, string value)
{
    if (address >= 0 && address < 256)
    {
        Instructions[address] = value;
    }
    else
    {
        cout << "invalid address";
    }
}

string Memory::getCell(int address)
{
    if (address >= 0 && address < 256)
    {
        return Instructions[address];
    }
    else
    {
        cout << "invalid address";
        return "XX"; //for non void return
    }
}
