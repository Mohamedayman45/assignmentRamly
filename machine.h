//
// Created by User on 10/24/2024.
//
#ifndef MACHINE_H
#define MACHINE_H
#include "memory.h"
#include "registerr.h"
#include "ALU.h"

using namespace std;

class machine
{
private:
public:
    void load1(int r, string value);
    void load2(int r, string value);
    void store(int r, int xy);

    void move(int r, int s);
    void Register1ToRegister2(int register1, int register2);
    void FloatingPointToRegister3(int register1, int register2, int register3);
    int jump(int registerNumber, int memoryAddressOp1, int i);
};

#endif
