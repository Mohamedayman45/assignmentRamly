//
// Created by User on 10/24/2024.
//
#include "memory.h"
#include "machine.h"
#include "registerr.h"
#include "ALU.h"
#include <bits/stdc++.h>

using namespace std;
vector<string> Instructions;

vector<string> Memory::ReadToVector(string name)
{

    ifstream instructionsFile(name);
    if (!instructionsFile.is_open())
    {
        cerr << "Error: Could not open Instructions File." << endl;
    }
    string line;
    while (getline(instructionsFile, line))
    {
        string word;
        stringstream ss(line);
        while (ss >> word)
        {
            Instructions.push_back(word.substr(0, 2));
            Instructions.push_back(word.substr(2, 2));
        }
    }
    for (int i = 0; i < Instructions.size(); i += 2)
    {
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
