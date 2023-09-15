#include "Memory.hpp"
#include "CPU.hpp"

// http://www.6502.org/users/obelisk/

int main() {
    CPU cpu;

    Memory memory;
    Memory::POWER_ON_RESET_LOC = 0x3333;

    cpu.reset(memory);

    memory[0x3333] = CPU::INS_LDA_IM;
    memory[0x3334] = 0xFF;

    cpu.execute(2, memory);

    return 0;
}