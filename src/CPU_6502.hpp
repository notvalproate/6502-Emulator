#pragma once
#include <iostream>
#include <vector>
#include "Memory.hpp"

struct CPU_6502 {
    CPU_6502(Memory& mem);

    //Internals

    Memory& Mem;

    Word PC;
    Byte SP;

    Byte A;
    Byte X;
    Byte Y;

    Bit C : 1;
    Bit Z : 1;
    Bit I : 1;
    Bit D : 1;
    Bit B : 1;
    Bit V : 1;
    Bit N : 1;

    u32 remainingCycles;
    Byte currentInstruction;

    Word fetchAddress;
    Word fetchAddressRelative;
    Byte fetchedValue;

    Bit Halt = 0;

    static int totalCycles;

    void fetch();

    void reset();
    void start();
    void clock();

    void irq();
    void nmi();

    //Addressing Modes

    void IMP(); void IMM();
    void ZP0(); void ZPX();
    void ZPY(); void REL();
    void ABS(); void ABX();
    void ABY(); void IND();
    void IZX(); void IZY();

    //Operations

    void ADC(); void AND(); void ASL(); void BCC();
    void BCS(); void BEQ(); void BIT(); void BMI();
    void BNE(); void BPL(); void BRK(); void BVC();
    void BVS(); void CLC(); void CLD(); void CLI();
    void CLV(); void CMP(); void CPX(); void CPY();
    void DEC(); void DEX(); void DEY(); void EOR();
    void INC(); void INX(); void INY(); void JMP();
    void JSR(); void LDA(); void LDX(); void LDY();
    void LSR(); void NOP(); void ORA(); void PHA();
    void PHP(); void PLA(); void PLP(); void ROL();
    void ROR(); void RTI(); void RTS(); void SBC();
    void SEC(); void SED(); void SEI(); void STA();
    void STX(); void STY(); void TAX(); void TAY();
    void TSX(); void TXA(); void TXS(); void TYA();

    void XXX(); //Invalid Opcode

    //Instruction Table

    struct Instruction {
        void(CPU_6502::*Operation)(void);
        void(CPU_6502::*AddressMode)(void);
        Byte requiredCycles;
    };

    using c = CPU_6502;

    static constexpr Instruction InstructionTable[256] = {
        {&c::BRK, &c::IMP, 7}, {&c::ORA, &c::IZX, 6}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::NOP, &c::IMP, 3}, {&c::ORA, &c::ZP0, 3}, {&c::ASL, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::PHP, &c::IMP, 3}, {&c::ORA, &c::IMM, 2},  {&c::ASL, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 4}, {&c::ORA, &c::ABS, 4}, {&c::ASL, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BPL, &c::REL, 2}, {&c::ORA, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::NOP, &c::IMP, 4}, {&c::ORA, &c::ZPX, 4}, {&c::ASL, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::CLC, &c::IMP, 2}, {&c::ORA, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::NOP, &c::IMP, 4}, {&c::ORA, &c::ABX, 4}, {&c::ASL, &c::ABX, 7}, {&c::XXX, &c::IMP, 7},
        {&c::JSR, &c::ABS, 6}, {&c::AND, &c::IZX, 6}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::BIT, &c::ZP0, 3}, {&c::AND, &c::ZP0, 3}, {&c::ROL, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::PLP, &c::IMP, 4}, {&c::AND, &c::IMM, 2},  {&c::ROL, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::BIT, &c::ABS, 4}, {&c::AND, &c::ABS, 4}, {&c::ROL, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BMI, &c::REL, 2}, {&c::AND, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 4}, {&c::AND, &c::ZPX, 4}, {&c::ROL, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::SEC, &c::IMP, 2}, {&c::AND, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::XXX, &c::IMP, 4}, {&c::AND, &c::ABX, 4}, {&c::ROL, &c::ABX, 7}, {&c::XXX, &c::IMP, 7},
        {&c::RTI, &c::IMP, 6}, {&c::EOR, &c::IZX, 6}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 3}, {&c::EOR, &c::ZP0, 3}, {&c::LSR, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::PHA, &c::IMP, 3}, {&c::EOR, &c::IMM, 2},  {&c::LSR, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::JMP, &c::ABS, 3}, {&c::EOR, &c::ABS, 4}, {&c::LSR, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BVC, &c::REL, 2}, {&c::EOR, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 4}, {&c::EOR, &c::ZPX, 4}, {&c::LSR, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::CLI, &c::IMP, 2}, {&c::EOR, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::XXX, &c::IMP, 4}, {&c::EOR, &c::ABX, 4}, {&c::LSR, &c::ABX, 7}, {&c::XXX, &c::IMP, 7},
        {&c::RTS, &c::IMP, 6}, {&c::ADC, &c::IZX, 6}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 3}, {&c::ADC, &c::ZP0, 3}, {&c::ROR, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::PLA, &c::IMP, 4}, {&c::ADC, &c::IMM, 2},  {&c::ROR, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::JMP, &c::IND, 5}, {&c::ADC, &c::ABS, 4}, {&c::ROR, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BVS, &c::REL, 2}, {&c::ADC, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 4}, {&c::ADC, &c::ZPX, 4}, {&c::ROR, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::SEI, &c::IMP, 2}, {&c::ADC, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::XXX, &c::IMP, 4}, {&c::ADC, &c::ABX, 4}, {&c::ROR, &c::ABX, 7}, {&c::XXX, &c::IMP, 7},
        {&c::NOP, &c::IMP, 2}, {&c::STA, &c::IZX, 6}, {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 6}, {&c::STY, &c::ZP0, 3}, {&c::STA, &c::ZP0, 3}, {&c::STX, &c::ZP0, 3}, {&c::XXX, &c::IMP, 3}, {&c::DEY, &c::IMP, 2}, {&c::NOP, &c::IMP, 2},  {&c::TXA, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::STY, &c::ABS, 4}, {&c::STA, &c::ABS, 4}, {&c::STX, &c::ABS, 4}, {&c::XXX, &c::IMP, 4},
        {&c::BCC, &c::REL, 2}, {&c::STA, &c::IZY, 6}, {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 6}, {&c::STY, &c::ZPX, 4}, {&c::STA, &c::ZPX, 4}, {&c::STX, &c::ZPY, 4}, {&c::XXX, &c::IMP, 4}, {&c::TYA, &c::IMP, 2}, {&c::STA, &c::ABY, 5},  {&c::TXS, &c::IMP, 2}, {&c::XXX, &c::IMP, 5}, {&c::NOP, &c::IMP, 5}, {&c::STA, &c::ABX, 5}, {&c::NOP, &c::IMP, 5}, {&c::XXX, &c::IMP, 5},
        {&c::LDY, &c::IMM, 2}, {&c::LDA, &c::IZX, 6}, {&c::LDX, &c::IMM, 2}, {&c::XXX, &c::IMP, 6}, {&c::LDY, &c::ZP0, 3}, {&c::LDA, &c::ZP0, 3}, {&c::LDX, &c::ZP0, 3}, {&c::XXX, &c::IMP, 3}, {&c::TAY, &c::IMP, 2}, {&c::LDA, &c::IMM, 2},  {&c::TAX, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::LDY, &c::ABS, 4}, {&c::LDA, &c::ABS, 4}, {&c::LDX, &c::ABS, 4}, {&c::XXX, &c::IMP, 4},
        {&c::BCS, &c::REL, 2}, {&c::LDA, &c::IZY, 5}, {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 5}, {&c::LDY, &c::ZPX, 4}, {&c::LDA, &c::ZPX, 4}, {&c::LDX, &c::ZPY, 4}, {&c::XXX, &c::IMP, 4}, {&c::CLV, &c::IMP, 2}, {&c::LDA, &c::ABY, 4},  {&c::TSX, &c::IMP, 2}, {&c::XXX, &c::IMP, 4}, {&c::LDY, &c::ABX, 4}, {&c::LDA, &c::ABX, 4}, {&c::LDX, &c::ABY, 4}, {&c::XXX, &c::IMP, 4},
        {&c::CPY, &c::IMM, 2}, {&c::CMP, &c::IZX, 6}, {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::CPY, &c::ZP0, 3}, {&c::CMP, &c::ZP0, 3}, {&c::DEC, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::INY, &c::IMP, 2}, {&c::CMP, &c::IMM, 2},  {&c::DEX, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::CPY, &c::ABS, 4}, {&c::CMP, &c::ABS, 4}, {&c::DEC, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BNE, &c::REL, 2}, {&c::CMP, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 4}, {&c::CMP, &c::ZPX, 4}, {&c::DEC, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::CLD, &c::IMP, 2}, {&c::CMP, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::XXX, &c::IMP, 4}, {&c::CMP, &c::ABX, 4}, {&c::DEC, &c::ABX, 7}, {&c::XXX, &c::IMP, 7},
        {&c::CPX, &c::IMM, 2}, {&c::SBC, &c::IZX, 6}, {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::CPX, &c::ZP0, 3}, {&c::SBC, &c::ZP0, 3}, {&c::INC, &c::ZP0, 5}, {&c::XXX, &c::IMP, 5}, {&c::INX, &c::IMP, 2}, {&c::SBC, &c::IMM, 2},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 2}, {&c::CPX, &c::ABS, 4}, {&c::SBC, &c::ABS, 4}, {&c::INC, &c::ABS, 6}, {&c::XXX, &c::IMP, 6},
        {&c::BEQ, &c::REL, 2}, {&c::SBC, &c::IZY, 5}, {&c::XXX, &c::IMP, 2}, {&c::XXX, &c::IMP, 8}, {&c::XXX, &c::IMP, 4}, {&c::SBC, &c::ZPX, 4}, {&c::INC, &c::ZPX, 6}, {&c::XXX, &c::IMP, 6}, {&c::SED, &c::IMP, 2}, {&c::SBC, &c::ABY, 4},  {&c::NOP, &c::IMP, 2}, {&c::XXX, &c::IMP, 7}, {&c::XXX, &c::IMP, 4}, {&c::SBC, &c::ABX, 4}, {&c::INC, &c::ABX, 7}, {&c::XXX, &c::IMP, 7}
    };
};