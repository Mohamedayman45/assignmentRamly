//
// Created by User on 10/24/2024.
//

#include "machine.h"
#include <bits/stdc++.h>
MemoryRegisters Registers;
void machine :: load1(int r, string value) {
    Registers.setRegister(r, value);
}
void machine ::load2(int r, string value) {
    Registers.setRegister(r , value);
}
void machine ::store(int r, int xy) {
    cout << "store";
    cout << "r is " << r << endl;
    cout << "xy is " << xy << endl;
}

void machine ::Register1ToRegister2(int register1, int register2) {
    Registers.setRegister(register2, Registers.getRegister(register1));
}

int machine ::jump(int registerNumber, int memoryAddressOp1, int i) {
    if (Registers.getRegister(registerNumber) == Registers.getRegister(0)){
        return memoryAddressOp1 - 2;
    }
    return i;
}
