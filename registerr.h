#include "memory.h"
#include <bits/stdc++.h>

#ifndef VOLE_MACHINE_REGISTERR_H
#define VOLE_MACHINE_REGISTERR_H

class MemoryRegister
{
private:
    static vector<string> registers;

public:
    MemoryRegister();
    void  setregister(int adress,string value);
    string getregister(int adress);
    int showregisterr();
};

#endif // VOLE_MACHINE_REGISTERR_H
