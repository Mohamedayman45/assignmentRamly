//
// Created by User on 10/24/2024.
//
#include "memory.h"

Memory::Memory() {

};

vector<string> Memory::Instructions(256, "00");
vector<string> Memory::ReadToVector(string name)
{
    ifstream instructionsFile(name);
    if (!instructionsFile.is_open())
    {
        cerr << "Error: Could not open Instructions File." << endl;
        return Instructions;
    }

    string line;
    int index = 0; // Index to keep track of where to overwrite

    while (getline(instructionsFile, line))
    {
        string word;
        stringstream ss(line);

        while (ss >> word && index < 256)
        {
            if (!isValidInstruction(word))
            {                                                            // Now valid since it's static
                cout << "Invalid Instruction Ignored: " << word << endl; // Print ignored instruction
                continue;                                                // Skip to the next word
            }

            // Add first two characters
            Instructions[index++] = word.substr(0, 2);
            if (index < 256)
            {
                Instructions[index++] = word.substr(2, 2); // Add next two characters
            }
        }
    }

    for (int i = 0; i < Instructions.size(); i += 2)
    {
        if (Instructions[i] == "00")
        { // To not print initialized 00s
            break;
        }
        cout << Instructions[i] << Instructions[i + 1] << endl;
    }

    instructionsFile.close();
    return Instructions;
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

bool Memory::isValidHexCharacter(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

bool Memory::isValidInstruction(const string &word)
{
    if (word.length() != 4)
    {
        return false; // We expect a fixed length of 4 characters
    }

    // Check the first character
    char firstChar = tolower(word[0]);
    if (!(firstChar >= '0' && firstChar <= '6') && firstChar != 'b' && firstChar != 'c')
    {
        return false; // Invalid first character
    }

    // Check the remaining three characters
    for (size_t i = 1; i < word.length(); ++i)
    {
        if (!isValidHexCharacter(word[i]))
        {
            return false; // Invalid character found
        }
    }

    return true; // All checks passed
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
        return "XX"; // for non void return
    }
}
void Memory::showMemory()
{
    // Print the top X-axis header
    cout << "   |";
    for (int x = 0; x < 16; x++)
    {
        cout << " " << setw(2) << setfill('0') << hex << uppercase << x << " ";
    }
    cout << "\n";

    // Print a separator line under the header
    cout << "---+" << string(16 * 4, '-') << "\n";

    // Iterate over each instruction, displaying values in a table format
    for (int i = 0; i < Instructions.size(); i++)
    {
        // Print the Y-axis address (leftmost column) at the start of each row
        if (i % 16 == 0)
        {
            cout << setw(2) << setfill('0') << hex << uppercase << i << " |";
        }

        // Print each value in two-digit hexadecimal format, properly spaced
        cout << " " << setw(2) << setfill('0') << hex << uppercase << Instructions[i] << " ";

        // Break the line after every 16 values to start a new row
        if ((i + 1) % 16 == 0)
        {
            cout << "\n";
        }
    }

    // Ensure the last line ends properly if the instructions don't fill a complete row
    if (Instructions.size() % 16 != 0)
    {
        cout << "\n";
    }
}
