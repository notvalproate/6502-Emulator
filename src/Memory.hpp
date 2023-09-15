#pragma once
#include <cassert>

using Bit = bool;
using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory {
    static constexpr u32 MAX_MEM = 1024 * 64;

    static Word POWER_ON_RESET_LOC;

    static Byte Data[MAX_MEM];

    void initialize();

    Byte operator[](u32 address) const;
    Byte& operator[](u32 address);
};