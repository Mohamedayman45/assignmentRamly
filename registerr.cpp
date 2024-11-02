//
// Created by User on 10/24/2024.
//

#include "registerr.h"
#include "memory.h"
#include "machine.h"
#include <bits/stdc++.h>

vector<string> MemoryRegisters::registers(16, "00");  // Initialize once

MemoryRegisters::MemoryRegisters() {
}

void MemoryRegisters ::setRegister(int address, string value)
{
    registers[address] = value;
}
string MemoryRegisters ::getRegister(int address) {
    return registers[address];
}
void MemoryRegisters ::showRegisters() {
    for (int i=0;i<registers.size();++i){
        cout <<"R" << i << " " << registers[i] << endl;
    }
}
