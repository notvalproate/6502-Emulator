#include "Memory.hpp"
#include "CPU.hpp"

// http://www.6502.org/users/obelisk/

int main() {
    Memory memory;
    Memory::POWER_ON_RESET_LOC = 0x3333;

    CPU cpu(memory);

    cpu.reset();

    memory[0x3333] = 0xA9;
    memory[0x3334] = 0x42;

    cpu.execute();

    return 0;
}