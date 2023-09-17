#include "CPU_6502.hpp"

//////////////////////////////
// LOAD AND STORE OPERATIONS /
//////////////////////////////


void CPU_6502::LDA() {
    A = fetchedValue;
    Z = A == 0;
    N = A & 0x80;
}

void CPU_6502::LDX() {
    X = fetchedValue;
    Z = X == 0;
    N = X & 0x80;
}

void CPU_6502::LDY() {
    Y = fetchedValue;
    Z = Y == 0;
    N = Y & 0x80;
}

void CPU_6502::STA() {
    Mem[fetchAddress] = A;
}

void CPU_6502::STX() {
    Mem[fetchAddress] = X;
}

void CPU_6502::STY() {
    Mem[fetchAddress] = Y;
}


///////////////////////
// REGISTER TRANSFERS /
///////////////////////


void CPU_6502::TAX() {
    X = A;
    Z = X == 0;
    N = X & 0x80;
}

void CPU_6502::TAY() {
    Y = A;
    Z = Y == 0;
    N = Y & 0x80;
}

void CPU_6502::TXA() {
    A = X;
    Z = A == 0;
    N = A & 0x80;
}

void CPU_6502::TYA() {
    A = Y;
    Z = A == 0;
    N = A & 0x80;
}


/////////////////////
// STACK OPERATIONS /
/////////////////////


void CPU_6502::TSX() {
    X = SP;
    Z = X == 0;
    N = X & 0x80;
} 

void CPU_6502::TXS() {
    SP = X;
} 

void CPU_6502::PHA() {
    Mem[0x0100 | SP] = A;
    SP--;
} 

void CPU_6502::PHP() {
    B = 1;
    Mem[0x0100 | SP] = (C << 0) | (Z << 1) | (I << 2) | (D << 3) | (B << 4) | (1 << 5) | (V << 6) | (N << 7);
    SP--;
}

void CPU_6502::PLA() {
    SP++;
    A = Mem[0x0100 | SP];
    Z = A == 0;
    N = A & 0x80;
}

void CPU_6502::PLP() {
    SP++;
    Byte Status = Mem[0x0100 | SP];

    C = Status & 1;
    Z = (Status >> 1) & 1;
    I = (Status >> 2) & 1;
    D = (Status >> 3) & 1;
    B = (Status >> 4) & 1;
    V = (Status >> 6) & 1;
    N = (Status >> 7) & 1;
}


////////////
// LOGICAL /
////////////


void CPU_6502::AND() {
    A = A & fetchedValue;
    Z = A == 0;
    N = A & 0x80;
}

void CPU_6502::EOR() {
    A = A ^ fetchedValue;
    Z = A == 0;
    N = A & 0x80;
} 

void CPU_6502::ORA() {
    A = A | fetchedValue;
    Z = A == 0;
    N = A & 0x80;
} 

void CPU_6502::BIT() {
    Z = ((fetchedValue & A) == 0);
    V = (fetchedValue >> 6) & 1;
    N = (fetchedValue >> 7) & 1; 
}

///////////////
// ARITHMETIC /
///////////////


void CPU_6502::ADC() {
    Word Result = (Word)A + (Word)fetchedValue + (Word)C;
    C = (Result >> 8) & 1;
    Z = (Result & 0xFF) == 0;
    N = Result & 0x80;
    V = (~(A ^ fetchedValue) & (A ^ Result)) & 0x80;
    A = Result & 0xFF;
}

void CPU_6502::SBC() {
    Byte Inverted = fetchedValue ^ 0xFF;

    Word Result = (Word)A + (Word)Inverted + (Word)C; 
    C = (Result >> 8) & 1; 
    Z = (Result & 0xFF) == 0; 
    N = Result & 0x80;
    V = (~(A ^ fetchedValue) & (A ^ Result)) & 0x80; 
    A = Result & 0xFF;
} 

void CPU_6502::CMP() {
    Word Result = (Word)A - (Word)fetchedValue;
    C = A >= fetchedValue;
    Z = (Result & 0xFF) == 0;
    N = Result & 0x80;
} 

void CPU_6502::CPX() {
    Word Result = (Word)X - (Word)fetchedValue;
    C = X >= fetchedValue;
    Z = (Result & 0xFF) == 0;
    N = Result & 0x80;
} 

void CPU_6502::CPY() {
    Word Result = (Word)Y - (Word)fetchedValue;
    C = Y >= fetchedValue;
    Z = (Result & 0xFF) == 0;
    N = Result & 0x80;
}


//////////////////////////////
// INCREMENTS AND DECREMENTS /
//////////////////////////////


void CPU_6502::INC() {
    Mem[fetchAddress]++;
    Z = Mem[fetchAddress] == 0;
    N = Mem[fetchAddress] & 0x80;
} 

void CPU_6502::INX() {
    X++;
    Z = X == 0;
    N = X & 0x80;
} 

void CPU_6502::INY() {
    Y++;
    Z = Y == 0;
    N = Y & 0x80;
} 

void CPU_6502::DEC() {
    Mem[fetchAddress]++;
    Z = Mem[fetchAddress] == 0;
    N = Mem[fetchAddress] & 0x80;
} 

void CPU_6502::DEX() {
    X--;
    Z = X == 0;
    N = X & 0x80;
} 

void CPU_6502::DEY() {
    Y--;
    Z = Y == 0;
    N = Y & 0x80;
}


///////////
// SHIFTS /
///////////


void CPU_6502::ASL() {
    C = (fetchedValue >> 7) & 1;

    Byte Result = fetchedValue << 1;

    if (InstructionTable[currentInstruction].AddressMode == &CPU_6502::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = Result == 0;
    N = (Result >> 7) & 1;
} 

void CPU_6502::LSR() {
    C = fetchedValue & 1;

    Byte Result = fetchedValue >> 1;

    if (InstructionTable[currentInstruction].AddressMode == &CPU_6502::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = Result == 0;
    N = 0;
} 

void CPU_6502::ROL() {
    Bit PreviousC = C;
    C = (fetchedValue >> 7) & 1;

    Byte Result = (fetchedValue << 1) + PreviousC;

    if (InstructionTable[currentInstruction].AddressMode == &CPU_6502::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = Result == 0;
    N = (Result >> 7) & 1;
} 

void CPU_6502::ROR() {
    Bit PreviousC = C;
    C = fetchedValue & 1;

    Byte Result = (fetchedValue >> 1) | (PreviousC << 7);

    if (InstructionTable[currentInstruction].AddressMode == &CPU_6502::IMP) { 
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = Result == 0; 
    N = PreviousC;
}


////////////////////
// JUMPS AND CALLS /
////////////////////


void CPU_6502::JMP() {
    PC = fetchAddress;
} 

void CPU_6502::JSR() {
    PC--;

    Mem[0x0100 | SP] = (PC >> 8) & 0xFF;
    SP--;
    Mem[0x0100 | SP] = PC & 0xFF;
    SP--;

    PC = fetchAddress;
} 

void CPU_6502::RTS() {
    SP++;
    PC = Mem[0x0100 | SP];
    SP++;
    PC |= Mem[0x0100 | SP] << 8;

    PC++;
}


/////////////
// BRANCHES /
/////////////


void CPU_6502::BCC() {
    if (C == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BCS() {
    if (C == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BEQ() {
    if (Z == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BMI() {
    if (N == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BNE() {
    if (Z == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BPL() {
    if (N == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BVC() {
    if (V == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU_6502::BVS() {
    if (V == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 


////////////////////////
// STATUS FLAG CHANGES /
////////////////////////


void CPU_6502::CLC() {
    C = 0;
} 

void CPU_6502::CLD() {
    D = 0;
} 

void CPU_6502::CLI() {
    I = 0;
} 

void CPU_6502::CLV() {
    V = 0;
} 

void CPU_6502::SEC() {
    C = 1;
} 

void CPU_6502::SED() {
    D = 1;
} 

void CPU_6502::SEI() {
    I = 1;
}


/////////////////////
// SYSTEM FUNCTIONS /
/////////////////////


void CPU_6502::BRK() {
    PC++;

    Mem[0x0100 | SP] = (PC >> 8) & 0xFF;
    SP--;

    Mem[0x0100 | SP] = PC & 0xFF;
    SP--;

    B = 1;
    I = 1;
    Mem[0x0100 | SP] = (C << 0) | (Z << 1) | (I << 2) | (D << 3) | (B << 4) | (1 << 5) | (V << 6) | (N << 7);
    B = 0;
    SP--;

    PC = Mem[0xFFFF] << 8 | Mem[0xFFFE];
}

void CPU_6502::NOP() {
    if (currentInstruction == 0x04) {
        Halt = 1;
    }
} 

void CPU_6502::RTI() {
    SP++;
    Byte Status = Mem[0x0100 | SP];

    C = Status & 1;
    Z = (Status >> 1) & 1;
    I = (Status >> 2) & 1;
    D = (Status >> 3) & 1;
    B = (Status >> 4) & 1;
    V = (Status >> 6) & 1;
    N = (Status >> 7) & 1;

    SP++;
    PC = Mem[0x0100 | SP];
    SP++;
    PC |= Mem[0x0100 | SP] << 8;
}

////////////////////
// INVALID OP CODE /
////////////////////


void CPU_6502::XXX() {
    return;
}


///////////////
// INTERRUPTS /
///////////////


void CPU_6502::irq() {
    if (I == 0) {
        Mem[0x0100 | SP] = (PC >> 8) & 0xFF;
        SP--;
        Mem[0x0100 | SP] = PC & 0xFF;
        SP--;

        B = 1;
        I = 1;
        Mem[0x0100 | SP] = (C << 0) | (Z << 1) | (I << 2) | (D << 3) | (B << 4) | (1 << 5) | (V << 6) | (N << 7);
        B = 0;
        SP--;

        PC = (Mem[0xFFFF] << 8) | Mem[0xFFFE];

        remainingCycles += 7;
    }
}

void CPU_6502::nmi() {
    Mem[0x0100 | SP] = (PC >> 8) & 0xFF;
    SP--;
    Mem[0x0100 | SP] = PC & 0xFF;
    SP--;

    B = 1;
    I = 1;
    Mem[0x0100 | SP] = (C << 0) | (Z << 1) | (I << 2) | (D << 3) | (B << 4) | (1 << 5) | (V << 6) | (N << 7);
    B = 0;
    SP--;

    PC = (Mem[0xFFFB] << 8) | Mem[0xFFFA];

    remainingCycles += 8;
}