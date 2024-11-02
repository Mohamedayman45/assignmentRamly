#include <bits/stdc++.h>

#ifndef MEMORY_H
#define MEMORY_H

using namespace std;

class memory
{
public:
    // Constructor that allows specifying the size

    static vector<string> ReadToVector(string filename); // file name in this function
    virtual void setCell(int address, string value);
    virtual string getCell(int address);
};

#endif
