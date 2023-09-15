#include "CPU.hpp"

Byte CPU::fetchByte(u32& cycles, Memory& memory) {
    Byte data = memory[PC];
    PC++;
    cycles--;
    return data;
}

void CPU::reset(Memory& memory) {
    memory.initialize();

    PC = (memory[0xFFFD] << 8) + memory[0xFFFC];
    SP = 0x0100;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
}

void CPU::execute(u32 cycles, Memory& memory) {
    while (cycles > 0) {
        Byte Ins = fetchByte(cycles, memory);

        switch (Ins) {
        case INS_LDA_IM:
        {
            Byte Value = fetchByte(cycles, memory);
            A = Value;
            Z = (A == 0);
            N = (A & 0b10000000) > 0;

            std::cout << "LDA_IM. A: " << (int)A << " flags: " << Z << " " << N << std::endl;
            std::cout << "Actual value:\n";

            if (N) {
                std::cout << "-" << (int)(0b10000000 - (A & 0b01111111));
            }
            else {
                std::cout << "+" << (int)(A & 0b01111111);
            }

        } break;

        default:
            break;
        }
    }
}