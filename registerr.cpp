//
// Created by User on 10/24/2024.
//

#include "registerr.h"
#include "memory.h"
#include "machine.h"
#include <bits/stdc++.h>

vector<string> MemoryRegister::registers(16, "00");  // Initialize once

MemoryRegister::MemoryRegister() {
}

void MemoryRegister ::setregister(int adress, string valuee)
{
    registers[adress]=valuee;
}
string MemoryRegister ::getregister(int adress) {
    return registers[adress];
}
int MemoryRegister ::showregisterr() {
    for (int i=0;i<registers.size();++i){
        cout <<"register " << i << " equall to " << registers[i] << endl;
    }
}
