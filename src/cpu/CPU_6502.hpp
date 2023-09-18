#pragma once
#include <iostream>
#include <vector>
#include "../Memory.hpp"

class CPU_6502 {
public:
    CPU_6502(Memory& mem);

    static int totalCycles;

    void reset();
    void start();
    void clock();

    void irq();
    void nmi();

private:
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

    //Some Helper functions

    void compareWith(Byte value);
    void branchIf(Bit flag);
    void interrupt(Bit brk);

    //Instruction Table

    struct Instruction {
        void(CPU_6502::*Operation)(void);
        void(CPU_6502::*AddressMode)(void);
        Byte requiredCycles;
    };

#define OP(ins, am, cycles) {&CPU_6502::##ins, &CPU_6502::##am, cycles}

    static constexpr Instruction InstructionTable[256] = {
        OP(BRK, IMP, 7), OP(ORA, IZX, 6), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(NOP, IMP, 3), OP(ORA, ZP0, 3), OP(ASL, ZP0, 5), OP(XXX, IMP, 5), OP(PHP, IMP, 3), OP(ORA, IMM, 2), OP(ASL, IMP, 2), OP(XXX, IMP, 2), OP(XXX, IMP, 4), OP(ORA, ABS, 4), OP(ASL, ABS, 6), OP(XXX, IMP, 6),
        OP(BPL, REL, 2), OP(ORA, IZY, 5), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(NOP, IMP, 4), OP(ORA, ZPX, 4), OP(ASL, ZPX, 6), OP(XXX, IMP, 6), OP(CLC, IMP, 2), OP(ORA, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(ORA, ABX, 4), OP(ASL, ABX, 7), OP(XXX, IMP, 7),
        OP(JSR, ABS, 6), OP(AND, IZX, 6), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(BIT, ZP0, 3), OP(AND, ZP0, 3), OP(ROL, ZP0, 5), OP(XXX, IMP, 5), OP(PLP, IMP, 4), OP(AND, IMM, 2), OP(ROL, IMP, 2), OP(XXX, IMP, 2), OP(BIT, ABS, 4), OP(AND, ABS, 4), OP(ROL, ABS, 6), OP(XXX, IMP, 6),
        OP(BMI, REL, 2), OP(AND, IZY, 5), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 4), OP(AND, ZPX, 4), OP(ROL, ZPX, 6), OP(XXX, IMP, 6), OP(SEC, IMP, 2), OP(AND, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(AND, ABX, 4), OP(ROL, ABX, 7), OP(XXX, IMP, 7),
        OP(RTI, IMP, 6), OP(EOR, IZX, 6), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 3), OP(EOR, ZP0, 3), OP(LSR, ZP0, 5), OP(XXX, IMP, 5), OP(PHA, IMP, 3), OP(EOR, IMM, 2), OP(LSR, IMP, 2), OP(XXX, IMP, 2), OP(JMP, ABS, 3), OP(EOR, ABS, 4), OP(LSR, ABS, 6), OP(XXX, IMP, 6),
        OP(BVC, REL, 2), OP(EOR, IZY, 5), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 4), OP(EOR, ZPX, 4), OP(LSR, ZPX, 6), OP(XXX, IMP, 6), OP(CLI, IMP, 2), OP(EOR, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(EOR, ABX, 4), OP(LSR, ABX, 7), OP(XXX, IMP, 7),
        OP(RTS, IMP, 6), OP(ADC, IZX, 6), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 3), OP(ADC, ZP0, 3), OP(ROR, ZP0, 5), OP(XXX, IMP, 5), OP(PLA, IMP, 4), OP(ADC, IMM, 2), OP(ROR, IMP, 2), OP(XXX, IMP, 2), OP(JMP, IND, 5), OP(ADC, ABS, 4), OP(ROR, ABS, 6), OP(XXX, IMP, 6),
        OP(BVS, REL, 2), OP(ADC, IZY, 5), OP(XXX, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 4), OP(ADC, ZPX, 4), OP(ROR, ZPX, 6), OP(XXX, IMP, 6), OP(SEI, IMP, 2), OP(ADC, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(ADC, ABX, 4), OP(ROR, ABX, 7), OP(XXX, IMP, 7),
        OP(NOP, IMP, 2), OP(STA, IZX, 6), OP(NOP, IMP, 2), OP(XXX, IMP, 6), OP(STY, ZP0, 3), OP(STA, ZP0, 3), OP(STX, ZP0, 3), OP(XXX, IMP, 3), OP(DEY, IMP, 2), OP(NOP, IMP, 2), OP(TXA, IMP, 2), OP(XXX, IMP, 2), OP(STY, ABS, 4), OP(STA, ABS, 4), OP(STX, ABS, 4), OP(XXX, IMP, 4),
        OP(BCC, REL, 2), OP(STA, IZY, 6), OP(NOP, IMP, 2), OP(XXX, IMP, 6), OP(STY, ZPX, 4), OP(STA, ZPX, 4), OP(STX, ZPY, 4), OP(XXX, IMP, 4), OP(TYA, IMP, 2), OP(STA, ABY, 5), OP(TXS, IMP, 2), OP(XXX, IMP, 5), OP(NOP, IMP, 5), OP(STA, ABX, 5), OP(NOP, IMP, 5), OP(XXX, IMP, 5),
        OP(LDY, IMM, 2), OP(LDA, IZX, 6), OP(LDX, IMM, 2), OP(XXX, IMP, 6), OP(LDY, ZP0, 3), OP(LDA, ZP0, 3), OP(LDX, ZP0, 3), OP(XXX, IMP, 3), OP(TAY, IMP, 2), OP(LDA, IMM, 2), OP(TAX, IMP, 2), OP(XXX, IMP, 2), OP(LDY, ABS, 4), OP(LDA, ABS, 4), OP(LDX, ABS, 4), OP(XXX, IMP, 4),
        OP(BCS, REL, 2), OP(LDA, IZY, 5), OP(NOP, IMP, 2), OP(XXX, IMP, 5), OP(LDY, ZPX, 4), OP(LDA, ZPX, 4), OP(LDX, ZPY, 4), OP(XXX, IMP, 4), OP(CLV, IMP, 2), OP(LDA, ABY, 4), OP(TSX, IMP, 2), OP(XXX, IMP, 4), OP(LDY, ABX, 4), OP(LDA, ABX, 4), OP(LDX, ABY, 4), OP(XXX, IMP, 4),
        OP(CPY, IMM, 2), OP(CMP, IZX, 6), OP(NOP, IMP, 2), OP(XXX, IMP, 8), OP(CPY, ZP0, 3), OP(CMP, ZP0, 3), OP(DEC, ZP0, 5), OP(XXX, IMP, 5), OP(INY, IMP, 2), OP(CMP, IMM, 2), OP(DEX, IMP, 2), OP(XXX, IMP, 2), OP(CPY, ABS, 4), OP(CMP, ABS, 4), OP(DEC, ABS, 6), OP(XXX, IMP, 6),
        OP(BNE, REL, 2), OP(CMP, IZY, 5), OP(NOP, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 4), OP(CMP, ZPX, 4), OP(DEC, ZPX, 6), OP(XXX, IMP, 6), OP(CLD, IMP, 2), OP(CMP, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(CMP, ABX, 4), OP(DEC, ABX, 7), OP(XXX, IMP, 7),
        OP(CPX, IMM, 2), OP(SBC, IZX, 6), OP(NOP, IMP, 2), OP(XXX, IMP, 8), OP(CPX, ZP0, 3), OP(SBC, ZP0, 3), OP(INC, ZP0, 5), OP(XXX, IMP, 5), OP(INX, IMP, 2), OP(SBC, IMM, 2), OP(NOP, IMP, 2), OP(XXX, IMP, 2), OP(CPX, ABS, 4), OP(SBC, ABS, 4), OP(INC, ABS, 6), OP(XXX, IMP, 6),
        OP(BEQ, REL, 2), OP(SBC, IZY, 5), OP(NOP, IMP, 2), OP(XXX, IMP, 8), OP(XXX, IMP, 4), OP(SBC, ZPX, 4), OP(INC, ZPX, 6), OP(XXX, IMP, 6), OP(SED, IMP, 2), OP(SBC, ABY, 4), OP(NOP, IMP, 2), OP(XXX, IMP, 7), OP(XXX, IMP, 4), OP(SBC, ABX, 4), OP(INC, ABX, 7), OP(XXX, IMP, 7)
    };
};

