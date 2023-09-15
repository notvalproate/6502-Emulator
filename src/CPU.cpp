#include "CPU.hpp"

Byte CPU::fetchByte() {
    Byte data = Mem[PC];
    PC++;
    remainingCycles--;
    return data;
}

void CPU::reset() {
    Mem.initialize();

    PC = (Mem[0xFFFD] << 8) | Mem[0xFFFC];
    SP = 0x00;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    remainingCycles = 0;
}

void CPU::execute() {
    if (remainingCycles == 0) {
        Byte opCode = fetchByte();
    }
}