#include "Memory.hpp"
#include "cpu/CPU_6502.hpp"

// All the materials and reference credit I am using for this project.
// http://www.6502.org/users/obelisk/
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.youtube.com/@javidx9

int main() {
    Memory memory(0x0400);
    CPU_6502 cpu(memory);

    // Complete test (including BCD) except interrupt test.
    memory.loadMemoryAt(0x000A, "tests/complete_test.bin");

    cpu.start();

    return 0;
}

// Might try to turn this into an NES emulator, looks like an interesting project to take on.
// Will be debugging this in x86 to make sure of compatibility in the future