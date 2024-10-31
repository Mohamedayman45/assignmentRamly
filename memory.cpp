//
// Created by User on 10/24/2024.
//
#include "memory.h"
#include "machine.h"
#include "registerr.h"
#include "ALU.h"
#include <bits/stdc++.h>

using namespace std;
vector<string> Instructions;
memory Cell;
vector<string> memory::ReadToVector(string name)
{

    ifstream instructionsFile(name);
    if (!instructionsFile.is_open())
    {
        cerr << "Error: Could not open Instructions File." << endl;
    }
    string line;
    while (getline(instructionsFile, line))
    {
        string word;
        stringstream ss(line);
        while (ss >> word)
        {
            Instructions.push_back(word.substr(0, 2));
            Instructions.push_back(word.substr(2, 2));
        }
    }
    for (int i=0;i < Instructions.size();i+=2){
        cout << Instructions[i] << Instructions[i+1]<<  endl;
    }
    instructionsFile.close();
    ALU XY;
    machine h;
    int op;
    for (int i=0;i<Instructions.size();i+=2){
        if(Instructions[i].substr(0,1)=="B"){
            op =7;
        }
        else if (Instructions[i].substr(0,1)=="C"){
            op=8;
        }
        else {
            op = stoi(Instructions[i].substr(0, 1));
        }
        int r= stoi(Instructions[i].substr(1,1));
        int xy= XY.hextodec(Instructions[i+1]);
        string value = Cell.getCell(xy);
        switch (op) {
            case 1:
                h.load1(r,value);
                break;
            case 2:
                h.load2(r,Instructions[i+1]);
                break;
        }
    }
    MemoryRegister coutt;
    coutt.showregisterr();

    return Instructions;
}
void memory::setCell(int adress, string value)
{
    if (adress >= 0 && adress < 256){
        Instructions[adress]=value;
    }
    else{
        cout << "invalid address";
    }

}

string memory::getCell(int adress)
{
    if (adress >= 0 && adress < 256){
        return Instructions[adress];
    }
    else{
        cout << "invalid address";
    }
}
