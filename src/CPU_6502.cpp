#include "CPU_6502.hpp"

CPU_6502::CPU_6502(Memory& mem) : Mem(mem) {
    reset();
}

void CPU_6502::fetch() {
    if (InstructionTable[currentInstruction].AddressMode == &CPU_6502::IMP) {
        return;
    }

    fetchedValue = Mem[fetchAddress];
}

void CPU_6502::reset() {
    Mem.initialize();

    PC = (Mem[0xFFFD] << 8) | Mem[0xFFFC];
    SP = 0xFF;

    fetchAddress = 0x0000;
    fetchedValue = 0x00;
    fetchAddressRelative = 0x0000;

    Halt = 0;

    C = Z = D = B = V = N = 0;
    I = 1;

    A = X = Y = 0;

    remainingCycles = 8;
    currentInstruction = 0x00;
}

void CPU_6502::start() {
    while (!Halt) {
        clock();
    }
}

// 0011 0000
// 

void CPU_6502::clock() {
    if (remainingCycles == 0) {
        if (PC == 0x3469) {
            __debugbreak();
        }

        currentInstruction = Mem[PC];
        PC++;

        remainingCycles += 2;

        (this->*InstructionTable[currentInstruction].AddressMode)();

        fetch();

        (this->*InstructionTable[currentInstruction].Operation)();
    }
    
    remainingCycles--;
}