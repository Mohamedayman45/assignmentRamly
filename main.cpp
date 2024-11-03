// #include "cpu.h"
#include "memory.h"
#include "machine.h"
#include "registerr.h"
#include "ALU.h"

using namespace std;

int main()
{
    // string fileName;
    // cin >> fileName;
    
    vector<string> Instructions = Memory::ReadToVector("instructions.txt");
    
    Memory Cell;
    ALU Alu;
    machine Vole;
    int op;
    for (int i = 0; i < Instructions.size(); i += 2)
    {
        // Instructions[i] is instruction number and register number
        // Instructions[i + 1] is memory value saved at address i + 1 in (decimal)
        
        if (Instructions[i].substr(0, 1) == "B")
        {
            op = 7;
        }
        else if (Instructions[i].substr(0, 1) == "C")
        {
            op = 8;
        }
        else
        {
            op = stoi(Instructions[i].substr(0, 1));
        }
        int registerNumber = Alu.hexToDec(Instructions[i].substr(1, 1));
        int memoryAddressOp1 = Alu.hexToDec(Instructions[i + 1]);
        string value = Cell.getCell(memoryAddressOp1);
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


        //TODO TASK 3
        // 3 RXY STORE the bit pattern found in register R in the memory cell whose address is XY.
        // Example: 35B1 would cause the contents of register 5 to be placed in the memory cell whose address is B1.
        // 3 R00 STORE to location 00, which is a memory mapping for the screen. Writing to 00 is writing to screen.
        // case 3:                         // UNCOMMENT when implementing


        //TODO TASK 4
        // 4 0RS MOVE the bit pattern found in register R to register S.
        // Example: 40A4 would cause the contents of register A to be copied into register 4.
        case 4: {                    // UNCOMMENT when implementing
            registerNumber = Alu.hexToDec(Instructions[i + 1].substr(0, 1));
            int register2Number = Alu.hexToDec(Instructions[i + 1].substr(1, 1));
            Vole.Register1ToRegister2(registerNumber, register2Number);
            break;
        }
        //TODO TASK 5
        // 5 RST ADD the bit patterns in registers S and T as though they were two’s complement representations
        // and leave the result in register R.
        // Example: 5726 would cause the binary values in registers 2 and 6 to be added and the sum placed in register 7.
        // case 5:                          // UNCOMMENT when implementing
        


        //TODO TASK 6
        // 6 RST ADD the bit patterns in registers S and T as though they represented values in floating-point
        // notation and leave the floating-point result in register R.
        // Example: 634E would cause the values in registers 4 and E to be added as floating-point values
        // and the result to be placed in register 3.
        // case 6:                         // UNCOMMENT when implementing


        //TODO TASK 7
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
            return 0; // HALT execution

        default:
            MemoryRegisters Registers;
            Registers.showRegisters();
            cout << "Invalid operation encountered. Halting execution." << endl;
            return 0; // HALT execution in case of an invalid operation

        }



    }
    MemoryRegisters Registers;
    Registers.showRegisters();
    

}


