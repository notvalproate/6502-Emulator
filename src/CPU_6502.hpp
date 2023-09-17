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
    };

    using c = CPU_6502;

    static constexpr Instruction InstructionTable[256] = {
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
};