//
// Created by User on 10/24/2024.
//

#include "machine.h"
#include <bits/stdc++.h>
MemoryRegisters toCompareReg;
void machine :: load1(int r, string value) {
    MemoryRegisters Registers;
    Registers.setRegister(r, value);
}
void machine ::load2(int r, string value) {
    MemoryRegisters Registers;
    Registers.setRegister(r , value);
}
void machine ::store(int r, int xy) {
    cout << "store";
    cout << "r is " << r << endl;
    cout << "xy is " << xy << endl;
}
int machine ::jump(int registerNumber, int memoryAddressOp1) {
    if (toCompareReg.getRegister(registerNumber)==toCompareReg.getRegister(0)){
        if (memoryAddressOp1%2==0) {
            return memoryAddressOp1 - 2;
        }
        else{
            return memoryAddressOp1 - 1;
        }
    }
}
