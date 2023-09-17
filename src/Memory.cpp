#include "Memory.hpp"
#include <iostream>
#include <fstream>

Byte Memory::Data[MAX_MEM] = { 0 };
Word Memory::RESET_VECTOR = 0x2000;
Word Memory::IRQ_HANDLER = 0x4000;
Word Memory::NMI_HANDLER = 0x8000;

void Memory::initialize() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0;
    }

    Data[0xFFFD] = RESET_VECTOR >> 8;
    Data[0xFFFC] = RESET_VECTOR;

    Data[0xFFFF] = IRQ_HANDLER >> 8;
    Data[0xFFFE] = IRQ_HANDLER;

    Data[0xFFFB] = NMI_HANDLER >> 8;
    Data[0xFFFA] = NMI_HANDLER;
}

void Memory::loadMemoryAt(Word address, const std::string& path) {
    FILE* fp;

    if (fopen_s(&fp, path.c_str(), "rb") != 0) {
        std::cout << "Failed to load file into memory!\nFile Path: " << path << "\nNOTE: File paths are relative to solution folder!" << std::endl;
        return;
    }
   
    fseek(fp, 0, SEEK_END);
    auto fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto count = fread(&Data[address], 1, fileSize, fp);

    if (count == fileSize) {
        std::cout << "Successfully loaded file fully into memory!\nBytes succesfully loaded: " << count << std::endl;
    }
    else {
        std::cout << "Partially loaded file into memory!\nBytes successfully loaded: " << count << "\nBytes that couldnt load: " << fileSize - count << std::endl;
    }

    fclose(fp);
}

Byte Memory::operator[](u32 address) const {
    assert(address < MAX_MEM);
    return Data[address];
}

Byte& Memory::operator[](u32 address) {
    assert(address < MAX_MEM);
    return Data[address];
}