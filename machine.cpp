//
// Created by User on 10/24/2024.
//
using namespace std;
#include "machine.h"
#include <bits/stdc++.h>
void machine ::filee(string name) {
    ifstream file(name);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Process each line here
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}