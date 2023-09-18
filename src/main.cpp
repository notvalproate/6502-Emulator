#include "Memory.hpp"
#include "CPU_6502.hpp"

// All the materials and reference credit I am using for this project.
// http://www.6502.org/users/obelisk/
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.youtube.com/@javidx9

void main() {
    Memory memory(0x0400);
    CPU_6502 cpu(memory);

    cpu.reset();

    memory.loadMemoryAt(0x000A, "tests/decimal_test.bin");

    cpu.start();
}