#include "machine.h"
#include <bits/stdc++.h>
int getIntegerInput()
{
    string input;
    int value;

    while (true)
    {
        getline(cin, input);    // Read the entire line
        stringstream ss(input); // Create a stringstream from the input string

        // Try to extract the integer and ensure the whole line was used
        if (ss >> value && ss.eof())
        {
            return value; // Return the integer if valid
        }
        else
        {
            cout << "Please enter a valid integer.\n";
        }
    }
}

void showMenu()
{
    cout << "==============================\n";
    cout << "      Main Menu\n";
    cout << "==============================\n";
    cout << "1) Display Registers\n";
    cout << "2) Display Program Counter\n";
    cout << "3) Display IR\n";
    cout << "4) Display Memory\n";
    cout << "5) Exit Program\n";
    cout << "==============================\n";
    cout << "Please choose an option (1-5): ";
}

int main()
{
    string fileName;
    cout << "Enter the name of the file to read the instructions: " << endl;
    cin >> fileName;

    ifstream isOpenFile(fileName);
    while (!isOpenFile.is_open()) {
        cout << "Error: Could not open Instructions File. \nPlease re-enter a valid file name: ";
        cin >> fileName;
        isOpenFile.open(fileName);
    }
    cout << "Opening File... \n" << endl;

    Memory Memory;
    vector<string> Instructions = Memory.ReadToVector("instructions.txt");
    MemoryRegisters Registers;
    ALU Alu;
    machine Vole;
    int op;
    bool halt = false;
    char DisplayRegStepByStep;
    cout << "Display Registers step by step ?" << endl
        << "Y for displaying step by step, else not" << endl;
    cin >> DisplayRegStepByStep;
    char DisplayMemStepByStep;
    cout << "Display Memory step by step ?" << endl
        << "Y for displaying step by step, else not" << endl;
    cin >> DisplayMemStepByStep;
    int RegisterCounter = 0;
    int MemoryCounter = 0;
    int programCounter;
    for (int i = 0; i < Instructions.size(); i += 2)
    {
        // Instructions[i] is instruction number and register number
        // Instructions[i + 1] is memory value saved at address i + 1 in (decimal)
        char firstChar = toupper(Instructions[i][0]);
        if (halt)
        {
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
        int memoryAddressOp2 = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
        int memoryAddressOp3 = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
        string value = Memory.getCell(memoryAddressOp1);

        programCounter = i;
        switch (op)
        {

        // 1 RXY LOAD the register R with the bit pattern found in the memory cell whose address is XY.
        // Example: 14A3 would cause the contents of the memory cell located at address A3 to be placed in register 4.
        case 1:
            Vole.load1(registerNumber, value);
            break;

            // 2 RXY LOAD the register R with the bit pattern XY.
            // Example: 20A3 would cause the value A3 to be placed in register 0.

        case 2:
            Vole.load2(registerNumber, Instructions[i + 1]);
            break;

        // 3 RXY STORE the bit pattern found in register R in the memory cell whose address is XY.
        case 3:
            Vole.store(registerNumber, memoryAddressOp1);
            break;

        // 4 0RS MOVE the bit pattern found in register R to register S.
        // Example: 40A4 would cause the contents of register A to be copied into register 4.
        case 4:
        {
            registerNumber = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
            int register2Number = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
            Vole.Register1ToRegister2(registerNumber, register2Number);
            break;
        }

        case 5:
            Vole.add(registerNumber, memoryAddressOp2, memoryAddressOp3);
            break;

        // TODO TASK 6
        //  6 RST ADD the bit patterns in registers S and T as though they represented values in floating-point
        //  notation and leave the floating-point result in register R.
        case 6:
        {
            registerNumber = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
            int register2Number = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
            int register3Number = Alu.hexToDec(Instructions[i].substr(1, 1));
            Vole.FloatingPointToRegister3(registerNumber, register2Number, register3Number);
        }
        // B RXY JUMP to the instruction located in the memory cell at address XY if the bit pattern in register R
        // is equal to the bit pattern in register number 0. Otherwise, continue with the normal sequence of
        // execution. (The jump is implemented by copying XY into the program counter during the execute phase.)
        case 7:
        {
            // Use a block for `case 7` to prevent scope conflicts
            i = Vole.jump(registerNumber, memoryAddressOp1, i);
            break;
        }

        case 8:
            halt = true;
            break; // HALT execution

        default:
            Registers.showRegisters();
            Memory.showMemory();
            i += 2;
            cout << "Invalid operation encountered! Halting Program..." << endl;
            halt = true;
            break;
        }
        if (toupper(DisplayRegStepByStep) == 'Y')
        {
            cout << "the Registers after instruction number " << ++RegisterCounter << endl;
            Registers.showRegisters();
        }
        if (toupper(DisplayMemStepByStep) == 'Y')
        {
            cout << "the Registers after instruction number " << ++MemoryCounter << endl;
            Memory.showMemory();
        }
    }

    while (true)
    {
        showMenu();
        int ToDo = getIntegerInput();
        if (ToDo == 1)
        {
            Registers.showRegisters();
        }
        else if (ToDo == 2)
        {
            cout << "Program Counter: " << programCounter << endl;
        }
        else if (ToDo == 3)
        {
            cout << "IR: " << op << endl;
        }
        else if (ToDo == 4)
        {
            Memory.showMemory();
        }
        else if (ToDo == 5)
        {
            break;
        }
    }
}
