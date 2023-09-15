#include "Memory.hpp"

Byte Memory::Data[MAX_MEM] = { 0 };
Word Memory::POWER_ON_RESET_LOC = 0x1000;

void Memory::initialize() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0;
    }

    Data[0xFFFD] = POWER_ON_RESET_LOC >> 8;
    Data[0xFFFC] = POWER_ON_RESET_LOC;
}

Byte Memory::operator[](u32 address) const {
    assert(address < MAX_MEM);
    return Data[address];
}

Byte& Memory::operator[](u32 address) {
    assert(address < MAX_MEM);
    return Data[address];
}