//
// Created by User on 10/24/2024.
//
#include "memory.h"
#include <bits/stdc++.h>
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
    return Instructions;

}
void memory::setCell(int adress, string value){
    
}

string memory::getCell(int adress) {
    
}