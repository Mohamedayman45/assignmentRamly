//
// Created by User on 10/24/2024.
//

#include "machine.h"
#include <bits/stdc++.h>

void machine :: load1(int r, string value) {
    MemoryRegister get;
    get.setregister(r, value);
}
void machine ::load2(int r, string valuee) {
    MemoryRegister set;
    set.setregister(r ,valuee);
}
void machine ::store(int r, int xy) {
    cout << "store";
    cout << "r is " <<r << endl;
    cout << "xy is " << xy << endl;
}
