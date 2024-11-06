#include <bits/stdc++.h>
#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>

using namespace std;

class Memory
{
public:
    Memory();                                     // Constructor declaration
    vector<string> ReadToVector(string filename); // Instance method
    string getCell(int address);                  // Instance method
    virtual void setCell(int address, string value);
    static vector<string> Instructions; // Instance member
    void showMemory();

private:
    bool isValidHexCharacter(char c);            // Instance validation function
    bool isValidInstruction(const string &word); // Instance validation function
};

#endif // MEMORY_H
