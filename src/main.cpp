#include "Memory.hpp"
#include "CPU.hpp"

// http://www.6502.org/users/obelisk/

int main() {
    Memory memory;
    CPU cpu(memory);

    cpu.reset();
 

    memory[0x2000] = 0x38;

    memory[0x2001] = 0xF8;
             
    memory[0x2002] = 0x08;
             
    memory[0x2003] = 0xBA;

    memory[0x2004] = 0xE8;
              
    memory[0x2005] = 0xBD;
    
    memory[0x2006] = 0x00;

    memory[0x2007] = 0x01;

    memory[0x2008] = 0x02;

    cpu.start();

    return 0;
}