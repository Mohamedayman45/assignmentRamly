#include "memory.h"
#include <bits/stdc++.h>

#ifndef VOLE_MACHINE_REGISTER_H
#define VOLE_MACHINE_REGISTER_H

class MemoryRegisters
{
private:
    static vector<string> registers;
public:
    MemoryRegisters();
    void setRegister(int address, string value);
    string getRegister(int address);
    void showRegisters();
};

#endif // VOLE_MACHINE_REGISTER_H
