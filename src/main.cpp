#include "Memory.hpp"
#include "CPU_6502.hpp"

// http://www.6502.org/users/obelisk/

void main() {
    Memory memory(0x0400);
    CPU_6502 cpu(memory);
    
    cpu.reset();

    memory.loadMemoryAt(0x000A, "tests/functional_test.bin");

    cpu.start();
}