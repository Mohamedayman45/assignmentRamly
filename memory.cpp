//
// Created by User on 10/24/2024.
//
#include "memory.h"
#include "machine.h"
#include "ALU.h"
#include <bits/stdc++.h>

using namespace std;
vector <string> memory::ReadToVector(string name) {

    ifstream instructionsFile(name);
    vector <string> Instructions;
    if (!instructionsFile.is_open()) {
        cerr << "Error: Could not open Instructions File." << endl;
    }
    string line;
    while(getline(instructionsFile, line)){
        string word;
        stringstream ss(line);
        while (ss >> word){
            Instructions.push_back(word.substr(0, 2));
            Instructions.push_back(word.substr(2, 2));
            
        }
    }
    instructionsFile.close();
    ALU XY;
    machine h;
    for (int i=0;i<Instructions.size();i+=2){
        int op;
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
        switch (op) {
            case 1:
                h.load1(r,xy);
                break;
            case 2:
                h.load2(r,xy);
                break;
            case 3:
                h.store(r,xy);
                break;
        }
    }
    return Instructions;

}
void memory::setCell(int adress, string value){
    
}

string memory::getCell(int adress) {
    
}
