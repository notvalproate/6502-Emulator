#include "CPU_6502.hpp"

/////////////////////////////////////
// IMPLIED, IMMEDIATE, AND RELATIVE /
/////////////////////////////////////


void CPU_6502::IMP() {
    fetchedValue = A;
}

void CPU_6502::IMM() {
    fetchAddress = PC;
    PC++;
}

void CPU_6502::REL() {
    fetchAddressRelative = Mem[PC];
    PC++;

    if (fetchAddressRelative & 0x80) {
        fetchAddressRelative |= 0xFF00;
    }
}


//////////////
// ZERO PAGE /
//////////////


void CPU_6502::ZP0() {
    fetchAddress = Mem[PC];
    PC++;
}

void CPU_6502::ZPX() {
    fetchAddress = (Mem[PC] + X) & 0x00FF;
    PC++;
}

void CPU_6502::ZPY() {
    fetchAddress = (Mem[PC] + Y) & 0x00FF;
    PC++;
}


/////////////
// ABSOLUTE /
/////////////


void CPU_6502::ABS() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    fetchAddress = (high << 8) | low;
}

void CPU_6502::ABX() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;


    fetchAddress = ((high << 8) | low) + X;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}

void CPU_6502::ABY() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    fetchAddress = ((high << 8) | low) + Y;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}


/////////////
// INDIRECT /
/////////////


void CPU_6502::IND() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    Word ptr = (high << 8) | low;

    //HARDWARE BUG, PAGE (HIGH BYTE) DOES NOT INCREMENT WHEN LOW BYTE IS 0xFF
    if (low == 0xFF) {
        fetchAddress = (Mem[ptr & 0xFF00] << 8) | Mem[ptr];
    }
    else {
        fetchAddress = (Mem[ptr + 1] << 8) | Mem[ptr];
    }
}

void CPU_6502::IZX() {
    Byte ptr = Mem[PC];
    PC++;

    Byte low = Mem[(ptr + X) & 0x00FF];
    Byte high = Mem[(ptr + X + 1) & 0x00FF];

    fetchAddress = (high << 8) | low;
}

void CPU_6502::IZY() {
    Byte ptr = Mem[PC];
    PC++;

    Byte low = Mem[ptr];
    Byte high = Mem[(ptr + 1) & 0x00FF];

    fetchAddress = ((high << 8) | low) + Y;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}