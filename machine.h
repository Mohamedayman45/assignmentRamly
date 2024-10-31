//
// Created by User on 10/24/2024.
//
#ifndef MACHINE_H
#define MACHINE_H
#include "machine.h"
#include "memory.h"
#include "registerr.h"
#include <bits/stdc++.h>
using namespace std;

class machine
{
private:
public:
    void load1(int r, string value);
    void load2(int r, string valuee);
    void store(int r, int xy);
    void move(int r, int s);
};

#endif
