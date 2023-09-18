#include "CPU_6502.hpp"
#include <chrono>

int CPU_6502::totalCycles = 0;

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

    totalCycles = 0;
    remainingCycles = 8;
    currentInstruction = 0x00;
}

void CPU_6502::start() {
    auto start = std::chrono::high_resolution_clock::now();

    while (!Halt) {
        clock();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto durationS = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Total CPU Runtime: " << durationS.count() << "s" << durationMs.count() % 1000 << "ms" << std::endl;

    double frequency = (totalCycles / 1000000.0) / ((double)durationS.count() + ((durationMs.count() % 1000) / 1000.0));

    std::cout << "CPU Frequency: " << frequency << " Mhz" << std::endl;
}

void CPU_6502::clock() {
    if (remainingCycles == 0) {
        if (PC == 0x3469) {
            std::cout << "\nALL TESTS PASSED. \n\nTotal Cycles Taken: " << totalCycles << std::endl;
            Halt = 1;
        }

        currentInstruction = Mem[PC];
        PC++;

        remainingCycles += InstructionTable[currentInstruction].requiredCycles;

        (this->*InstructionTable[currentInstruction].AddressMode)();
        fetch();
        (this->*InstructionTable[currentInstruction].Operation)();

        totalCycles += remainingCycles;
    }
    
    remainingCycles--;
}