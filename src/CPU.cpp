#include "CPU.hpp"

CPU::CPU(Memory& mem) : Mem(mem) {
    reset();
}

void CPU::reset() {
    Mem.initialize();

    PC = (Mem[0xFFFD] << 8) | Mem[0xFFFC];
    fetchAddress = 0x0000;
    SP = 0x00;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    remainingCycles = 0;
}

void CPU::execute() {
    if (remainingCycles == 0) {
        currentInstruction = Mem[PC];
        PC++;
    }

    remainingCycles--;
}

using c = CPU;

CPU::Instruction CPU::InstructionTable[256] = {
    {&c::BRK, &c::IMP}, {&c::ORA, &c::IZX}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::NOP, &c::IMP}, {&c::ORA, &c::ZP0}, {&c::ASL, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::PHP, &c::IMP}, {&c::ORA, &c::IMM},  {&c::ASL, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::ORA, &c::ABS}, {&c::ASL, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BPL, &c::REL}, {&c::ORA, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::NOP, &c::IMP}, {&c::ORA, &c::ZPX}, {&c::ASL, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::CLC, &c::IMP}, {&c::ORA, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::NOP, &c::IMP}, {&c::ORA, &c::ABX}, {&c::ASL, &c::ABX}, {&c::XXX, &c::IMP},
    {&c::JSR, &c::ABS}, {&c::AND, &c::IZX}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::BIT, &c::ZP0}, {&c::AND, &c::ZP0}, {&c::ROL, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::PLP, &c::IMP}, {&c::AND, &c::IMM},  {&c::ROL, &c::IMP}, {&c::XXX, &c::IMP}, {&c::BIT, &c::ABS}, {&c::AND, &c::ABS}, {&c::ROL, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BMI, &c::REL}, {&c::AND, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::AND, &c::ZPX}, {&c::ROL, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::SEC, &c::IMP}, {&c::AND, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::AND, &c::ABX}, {&c::ROL, &c::ABX}, {&c::XXX, &c::IMP},
    {&c::RTI, &c::IMP}, {&c::EOR, &c::IZX}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::EOR, &c::ZP0}, {&c::LSR, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::PHA, &c::IMP}, {&c::EOR, &c::IMM},  {&c::LSR, &c::IMP}, {&c::XXX, &c::IMP}, {&c::JMP, &c::ABS}, {&c::EOR, &c::ABS}, {&c::LSR, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BVC, &c::REL}, {&c::EOR, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::EOR, &c::ZPX}, {&c::LSR, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::CLI, &c::IMP}, {&c::EOR, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::EOR, &c::ABX}, {&c::LSR, &c::ABX}, {&c::XXX, &c::IMP},
    {&c::RTS, &c::IMP}, {&c::ADC, &c::IZX}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::ADC, &c::ZP0}, {&c::ROR, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::PLA, &c::IMP}, {&c::ADC, &c::IMM},  {&c::ROR, &c::IMP}, {&c::XXX, &c::IMP}, {&c::JMP, &c::IND}, {&c::ADC, &c::ABS}, {&c::ROR, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BVS, &c::REL}, {&c::ADC, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::ADC, &c::ZPX}, {&c::ROR, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::SEI, &c::IMP}, {&c::ADC, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::ADC, &c::ABX}, {&c::ROR, &c::ABX}, {&c::XXX, &c::IMP},
    {&c::NOP, &c::IMP}, {&c::STA, &c::IZX}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::STY, &c::ZP0}, {&c::STA, &c::ZP0}, {&c::STX, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::DEY, &c::IMP}, {&c::NOP, &c::IMP},  {&c::TXA, &c::IMP}, {&c::XXX, &c::IMP}, {&c::STY, &c::ABS}, {&c::STA, &c::ABS}, {&c::STX, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BCC, &c::REL}, {&c::STA, &c::IZY}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::STY, &c::ZPX}, {&c::STA, &c::ZPX}, {&c::STX, &c::ZPY}, {&c::XXX, &c::IMP}, {&c::TYA, &c::IMP}, {&c::STA, &c::ABY},  {&c::TXS, &c::IMP}, {&c::XXX, &c::IMP}, {&c::NOP, &c::IMP}, {&c::STA, &c::ABX}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP},
    {&c::LDY, &c::IMM}, {&c::LDA, &c::IZX}, {&c::LDX, &c::IMM}, {&c::XXX, &c::IMP}, {&c::LDY, &c::ZP0}, {&c::LDA, &c::ZP0}, {&c::LDX, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::TAY, &c::IMP}, {&c::LDA, &c::IMM},  {&c::TAX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::LDY, &c::ABS}, {&c::LDA, &c::ABS}, {&c::LDX, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BCS, &c::REL}, {&c::LDA, &c::IZY}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::LDY, &c::ZPX}, {&c::LDA, &c::ZPX}, {&c::LDX, &c::ZPY}, {&c::XXX, &c::IMP}, {&c::CLV, &c::IMP}, {&c::LDA, &c::ABY},  {&c::TSX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::LDY, &c::ABX}, {&c::LDA, &c::ABX}, {&c::LDX, &c::ABY}, {&c::XXX, &c::IMP},
    {&c::CPY, &c::IMM}, {&c::CMP, &c::IZX}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CPY, &c::ZP0}, {&c::CMP, &c::ZP0}, {&c::DEC, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::INY, &c::IMP}, {&c::CMP, &c::IMM},  {&c::DEX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CPY, &c::ABS}, {&c::CMP, &c::ABS}, {&c::DEC, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BNE, &c::REL}, {&c::CMP, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CMP, &c::ZPX}, {&c::DEC, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::CLD, &c::IMP}, {&c::CMP, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CMP, &c::ABX}, {&c::DEC, &c::ABX}, {&c::XXX, &c::IMP},
    {&c::CPX, &c::IMM}, {&c::SBC, &c::IZX}, {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CPX, &c::ZP0}, {&c::SBC, &c::ZP0}, {&c::INC, &c::ZP0}, {&c::XXX, &c::IMP}, {&c::INX, &c::IMP}, {&c::SBC, &c::IMM},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::CPX, &c::ABS}, {&c::SBC, &c::ABS}, {&c::INC, &c::ABS}, {&c::XXX, &c::IMP},
    {&c::BEQ, &c::REL}, {&c::SBC, &c::IZY}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::SBC, &c::ZPX}, {&c::INC, &c::ZPX}, {&c::XXX, &c::IMP}, {&c::SED, &c::IMP}, {&c::SBC, &c::ABY},  {&c::NOP, &c::IMP}, {&c::XXX, &c::IMP}, {&c::XXX, &c::IMP}, {&c::SBC, &c::ABX}, {&c::INC, &c::ABX}, {&c::XXX, &c::IMP}
};

//Addressing Modes

void CPU::IMP() {
    fetchedValue = A;
}

void CPU::IMM() {
    fetchAddress = PC;
    PC++;
}

void CPU::ZP0() {
    fetchAddress = Mem[PC];
    PC++;
}

void CPU::ZPX() {
    fetchAddress = (Mem[PC] + X) & 0x00FF;
    PC++;
}

void CPU::ZPY() {
    fetchAddress = (Mem[PC] + Y) & 0x00FF;
    PC++;
}

void CPU::REL() {
    fetchAddressRelative = Mem[PC];
    PC++;

    if (fetchAddressRelative & 0x80) {
        fetchAddressRelative |= 0xFF00;
    }
}

void CPU::ABS() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    fetchAddress = (high << 8) | low;
}

void CPU::ABX() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    fetchAddress = ((high << 8) | low) + X;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}

void CPU::ABY() { 
    Byte low = Mem[PC]; 
    PC++;
    Byte high = Mem[PC]; 
    PC++;

    fetchAddress = ((high << 8) | low) + Y;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}

void CPU::IND() {
    Byte low = Mem[PC];
    PC++;
    Byte high = Mem[PC];
    PC++;

    Word ptr = (high << 8) | low;

    //HARDWARE BUG, PAGE (HIGH BYTE) DOES NOT GO UP WHEN LOW BYTE IS 0xFF
    if (low == 0xFF) {
        fetchAddress = (Mem[ptr & 0xFF00] << 8) | Mem[ptr];
    }
    else {
        fetchAddress = (Mem[ptr + 1] << 8) | Mem[ptr];
    }
}

void CPU::IZX() {
    Byte ptr = Mem[PC];
    PC++;

    Byte low = Mem[(ptr + X) & 0x00FF];
    Byte high = Mem[(ptr + X + 1) & 0x00FF];

    fetchAddress = (high << 8) | low;
}

void CPU::IZY() {
    Byte ptr = Mem[PC];
    PC++;

    Byte low = Mem[ptr];
    Byte high = Mem[(ptr + 1) & 0x00FF];

    fetchAddress = ((high << 8) | low) + Y;

    if ((fetchAddress & 0xFF00) != (high << 8)) {
        remainingCycles++;
    }
}