//
// Created by User on 10/24/2024.
//
#include "memory.h"
#include "machine.h"
#include "registerr.h"
#include "ALU.h"
#include <bits/stdc++.h>

using namespace std;
vector<string> Instructions(256, "00"); // Initializes the vector with 256 elements, all set to "00"

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
            // Overwrite elements in the Instructions vector
            Instructions[index++] = word.substr(0, 2);
            if (index < 256)
            {
                Instructions[index++] = word.substr(2, 2);
            }
        }
    }

    for (int i = 0; i < Instructions.size(); i += 2)
    {
        if (Instructions[i] == "00"){ // To not print initialized 00s
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
