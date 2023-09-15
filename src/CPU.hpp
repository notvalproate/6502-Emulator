#pragma once
#include <iostream>
#include "Memory.hpp"

struct CPU {
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

    static constexpr Byte INS_LDA_IM = 0xA9;

    typedef void (*Instruction)(CPU&);

    static constexpr Instruction InstructionSet[0xFF] = { };

    Byte fetchByte(u32& cycles, Memory& memory);

    void reset(Memory& memory);
    void execute(u32 cycles, Memory& memory);
};