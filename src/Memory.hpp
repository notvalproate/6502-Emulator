#pragma once
#include <cassert>
#include <string>

using Bit = bool;
using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory {
    Memory() = default;

    Memory(Word resetVector) {
        RESET_VECTOR = resetVector;
    }

    static constexpr u32 MAX_MEM = 1024 * 64;

    static Word RESET_VECTOR;
    static Word NMI_HANDLER;
    static Word IRQ_HANDLER;

    static Byte Data[MAX_MEM];

    void initialize();
    void loadMemoryAt(Word address, const std::string& path);

    Byte operator[](u32 address) const;
    Byte& operator[](u32 address);
};