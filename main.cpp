#include "machine.h"
#include <bits/stdc++.h>
int getIntegerInput() {
    string input;
    int value;

    while (true) {
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            return value;
        } else {
            cout << endl << "Please enter a valid integer." <<endl;
        }
    }
}

int main()
{
    string fileName;
    cout << "enter the name of the file to execute the instructions" << endl;
    cin >> fileName;
    ifstream isOpenFile(fileName);
    if (!isOpenFile.is_open()) {
        cerr << "Error: Could not open Instructions File." << endl;
        cin >> fileName;
    }

    Memory Memory;
    vector<string> Instructions = Memory.ReadToVector(fileName);
    MemoryRegisters Registers;
    ALU Alu;
    machine Vole;
    int op;
    bool halt = false;
    string DisplayRegStepByStep;
    cout << "Do you want to display the Register step by step ?" << endl
    << "Y for displaying if any they will not display step by step" << endl;
    cin >> DisplayRegStepByStep;
    string DisplayMemStepByStep;
    cout << "Do you want to display the Memory step by step ?" << endl
         << "Y for displaying if any they will not display step by step" << endl;
    cin >> DisplayMemStepByStep;
    int RegisterCounter=0;
    int MemoryCounter=0;
    for (int i = 0; i < Instructions.size(); i += 2)
    {
        // Instructions[i] is instruction number and register number
        // Instructions[i + 1] is memory value saved at address i + 1 in (decimal)
        char firstChar = toupper(Instructions[i][0]);
        if (halt) {
            break;
        }
        if (firstChar == 'B')
        {
            op = 7;
        }
        else if (firstChar == 'C')
        {
            op = 8;
        }
        else
        {
            op = stoi(Instructions[i].substr(0, 1));
        }
        int registerNumber = Alu.hexToDec(Instructions[i].substr(1, 1));
        int memoryAddressOp1 = Alu.hexToDec(Instructions[i + 1]);
        int memoryAddressOp2 = Alu.hexToDec(Instructions[i+1].substr(0, 1));
        int memoryAddressOp3 = Alu.hexToDec(Instructions[i+1].substr(1, 1));
        string value = Memory.getCell(memoryAddressOp1);
        string programCounter = Instructions[i];
        switch (op)
        {

        //1 RXY LOAD the register R with the bit pattern found in the memory cell whose address is XY.
        //Example: 14A3 would cause the contents of the memory cell located at address A3 to be placed in register 4.
        case 1:
            Vole.load1(registerNumber, value);
            break;


        //2 RXY LOAD the register R with the bit pattern XY.
        //Example: 20A3 would cause the value A3 to be placed in register 0.

        case 2:
            Vole.load2(registerNumber, Instructions[i + 1]);
            break;

        // 3 RXY STORE the bit pattern found in register R in the memory cell whose address is XY.
        // Example: 35B1 would cause the contents of register 5 to be placed in the memory cell whose address is B1.
        // 3 R00 STORE to location 00, which is a memory mapping for the screen. Writing to 00 is writing to screen.
        case 3:
            Vole.store(registerNumber, memoryAddressOp1);
            break;

                // 4 0RS MOVE the bit pattern found in register R to register S.
        // Example: 40A4 would cause the contents of register A to be copied into register 4.
        case 4: {                    // UNCOMMENT when implementing
            registerNumber = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
            int register2Number = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
            Vole.Register1ToRegister2(registerNumber, register2Number);
            break;
        }
        case 5:
            Vole.add(registerNumber, memoryAddressOp2, memoryAddressOp3);
            break;
        


        //TODO TASK 6
        // 6 RST ADD the bit patterns in registers S and T as though they represented values in floating-point
        // notation and leave the floating-point result in register R.
        // Example: 634E would cause the values in registers 4 and E to be added as floating-point values
        // and the result to be placed in register 3.
        case 6: {                         // UNCOMMENT when implementing
            registerNumber = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
            int register2Number = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
            int register3Number = Alu.hexToDec(Instructions[i].substr(1, 1));
            Vole.FloatingPointToRegister3(registerNumber, register2Number, register3Number);
        }
        // B RXY JUMP to the instruction located in the memory cell at address XY if the bit pattern in register R
        // is equal to the bit pattern in register number 0. Otherwise, continue with the normal sequence of
        // execution. (The jump is implemented by copying XY into the program counter during the execute phase.)
        // Example: B43C would first compare the contents of register 4 with the contents of register 0. If
        // the two were equal, the pattern 3C would be placed in the program counter so that the next
        // instruction executed would be the one located at that memory address. Otherwise,
        case 7: {
            // Use a block for `case 7` to prevent scope conflicts
            i = Vole.jump(registerNumber, memoryAddressOp1, i);
            break;
        }
        

        case 8:
            halt = true;
            break; // HALT execution

        default:
            Registers.showRegisters();
            i += 2;
            cout << "Invalid operation encountered! Ignoring Operation..." << endl;
            break;
        }
        if (DisplayRegStepByStep=="Y" || DisplayRegStepByStep=="y"){
            cout << "the Registers after instruction number "<< ++RegisterCounter << endl;
            Registers.showRegisters();
        }
        if (DisplayMemStepByStep=="Y" || DisplayMemStepByStep=="y"){
            cout << "the Registers after instruction number "<< ++MemoryCounter << endl;
            Memory.showMemory();
        }

    }
    cout << "what what do you want to do ? " << endl
    << "1)display the status of the REGISTERS " << endl
    << "2)display the status of the PC " << endl
    << "3)display the status of the IR " << endl
    << "4)display the status of the MEMORY " << endl
    << "5) if you want to exit the program";
    int ToDo=getIntegerInput();
    while (true) {
        if (ToDo==1) {
            Registers.showRegisters();
        }
        //else if (ToDo==2) {
        //display program counter
        //}
        //else if (ToDo==3) {
        //display IR
        //}
        else if (ToDo==4) {
            Memory.showMemory();
        }
        else if (ToDo==5){
            break;
        }
        cout << "what do you want to do ? " << endl
             << "1)display the status of the REGISTERS " << endl
             << "2)display the status of the PC " << endl
             << "3)display the status of the IR " << endl
             << "4)display the status of the MEMORY " << endl
             << "5) if you want to exit the program";
        ToDo=getIntegerInput();
    }
}

// Test Jump
// 2011
// 2104
// 2A25
// bA05
// 1721
// c000
