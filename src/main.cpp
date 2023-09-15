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

    memory[0x3335] = 0x48;

    memory[0x3336] = 0xA9;
    memory[0x3337] = 0x43;

    memory[0x3338] = 0x68;

    memory[0x3339] = 0x02;


    cpu.start();

    return 0;
}