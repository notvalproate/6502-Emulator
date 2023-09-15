#pragma once
#include <iostream>
#include "Memory.hpp"

struct CPU {
    CPU(Memory& mem) : Mem(mem) {
        reset();
    }

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

    Byte fetchByte();

    void reset();
    void execute();

    //Instructions

    struct Instruction {
        void(*Operation)(void);
        void(*AddressMode)(void);
    };

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
};