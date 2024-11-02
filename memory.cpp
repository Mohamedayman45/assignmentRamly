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
memory Cell;
vector<string> memory::ReadToVector(string name)
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
    ALU Alu;
    machine Vole;
    int op;
    for (int i = 0; i < Instructions.size(); i += 2)
    {
        // Instructions[i] is instruction number and register number
        // Instructions[i + 1] is memory value saved at address i + 1 in (decimal)
        
        if (Instructions[i].substr(0, 1) == "B")
        {
            op = 7;
        }
        else if (Instructions[i].substr(0, 1) == "C")
        {
            op = 8;
        }
        else
        {
            op = stoi(Instructions[i].substr(0, 1));
        }
        int registerNumber = stoi(Instructions[i].substr(1, 1));
        int memoryAddressOp1 = Alu.hexToDec(Instructions[i + 1]);
        string value = Cell.getCell(memoryAddressOp1);
        switch (op)
        {
        case 1:
            Vole.load1(registerNumber, value);
            break;
        case 2:
            Vole.load2(registerNumber, Instructions[i + 1]);
            break;
        }
    }

    MemoryRegisters Registers;
    Registers.showRegisters();

    return Instructions;
}
void memory::setCell(int address, string value)
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

string memory::getCell(int address)
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
