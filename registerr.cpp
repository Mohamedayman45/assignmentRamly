//
// Created by User on 10/24/2024.
//

#include "registerr.h"
#include "memory.h"
#include "machine.h"
#include <bits/stdc++.h>

vector<string> MemoryRegisters::registers(16, "00"); // Initialize once

MemoryRegisters::MemoryRegisters()
{
}

void MemoryRegisters ::setRegister(int address, string value)
{
    registers[address] = value;
}
string MemoryRegisters ::getRegister(int address)
{
    return registers[address];
}
void MemoryRegisters::showRegisters()
{
    // Print a header
    cout << "Register | Value\n";
    cout << "--------------------\n";

    // Iterate over each register and display it in a tabular format
    for (int i = 0; i < registers.size(); ++i)
    {
        // Print the register name in hexadecimal, aligned to the left
        cout << "R" << hex << uppercase << setw(1) << setfill('0') << i << "     | "
             << dec << setw(8) << setfill(' ') << right << registers[i] << "\n";
    }
}
