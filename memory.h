#include <bits/stdc++.h>

#ifndef MEMORY_H
#define MEMORY_H

using namespace std;

class Memory { // Renamed the class to Memory
public:
    static vector<string> ReadToVector(string filename);
    virtual void setCell(int address, string value);
    virtual string getCell(int address);
};

#endif
