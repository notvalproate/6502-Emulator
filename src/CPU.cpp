#include "CPU.hpp"

CPU::CPU(Memory& mem) : Mem(mem) {
    reset();
}

void CPU::fetch() {
    if (InstructionTable[currentInstruction].AddressMode == &CPU::IMP) {
        return;
    }

    fetchedValue = Mem[fetchAddress];
}

void CPU::reset() {
    Mem.initialize();

    PC = (Mem[0xFFFD] << 8) | Mem[0xFFFC];
    fetchAddress = 0x0000;
    SP = 0xFF;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    remainingCycles = 0;
}

void CPU::start() {
    while (!Halt) {
        clock();
    }
}

void CPU::clock() {
    if (remainingCycles == 0) {
        currentInstruction = Mem[PC];
        PC++;

        remainingCycles += 2;

        (this->*InstructionTable[currentInstruction].AddressMode)();

        fetch();

        (this->*InstructionTable[currentInstruction].Operation)();
    }
    
    remainingCycles--;
}