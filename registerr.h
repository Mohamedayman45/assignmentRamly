#include "memory.h"
#include <bits/stdc++.h>

#ifndef VOLE_MACHINE_REGISTERR_H
#define VOLE_MACHINE_REGISTERR_H


class MemoryRegister : public memory {
    private:
        vector <string> registers;
    public:
        MemoryRegister() : registers(16, "00") {}
        
};

#endif // VOLE_MACHINE_REGISTERR_H
