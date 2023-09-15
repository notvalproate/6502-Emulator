#include "CPU.hpp"

//////////////////////////////
// LOAD AND STORE OPERATIONS /
//////////////////////////////


void CPU::LDA() {
    A = fetchedValue;
    Z = (A == 0);
    N = (A & 0x80) > 0;
}

void CPU::LDX() {
    X = fetchedValue;
    Z = (X == 0);
    N = (X & 0x80) > 0;
}

void CPU::LDY() {
    Y = fetchedValue;
    Z = (Y == 0);
    N = (Y & 0x80) > 0;
}

void CPU::STA() {
    Mem[fetchAddress] = A;
}

void CPU::STX() {
    Mem[fetchAddress] = X;
}

void CPU::STY() {
    Mem[fetchAddress] = Y;
}


///////////////////////
// REGISTER TRANSFERS /
///////////////////////


void CPU::TAX() {
    X = A;
    Z = (X == 0);
    N = (X & 0x80) > 0;
}

void CPU::TAY() {
    Y = A;
    Z = (Y == 0);
    N = (Y & 0x80) > 0;
}

void CPU::TXA() {
    A = X;
    Z = (A == 0);
    N = (A & 0x80) > 0;
}

void CPU::TYA() {
    A = Y;
    Z = (A == 0);
    N = (A & 0x80) > 0;
}


/////////////////////
// STACK OPERATIONS /
/////////////////////


void CPU::TSX() {
    X = SP;
    Z = (X == 0);
    N = (X & 0x80) > 0;
} 

void CPU::TXS() {
    SP = X;
} 

void CPU::PHA() {
    Mem[0x0100 | SP] = A;
    SP--;
} 

void CPU::PHP() {
    Mem[0x0100 | SP] = (C << 0) | (Z << 1) | (I << 2) | (D << 3) | (B << 4) | (1 << 5) | (V << 6) | (N << 7);
    SP--;
}

void CPU::PLA() {
    SP++;
    A = Mem[0x0100 | SP];
    Z = (A == 0);
    N = (A & 0x80) > 0;
}

void CPU::PLP() {
    SP++;
    Byte Status = Mem[0x100 | SP];

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


void CPU::AND() {
    A = A & fetchedValue;
    Z = (A == 0);
    N = (A & 0x80) > 0;
}

void CPU::EOR() {
    A = A ^ fetchedValue;
    Z = (A == 0);
    N = (A & 0x80) > 0;
} 

void CPU::ORA() {
    A = A | fetchedValue;
    Z = (A == 0);
    N = (A & 0x80) > 0;
} 

void CPU::BIT() {
    Z = ((fetchedValue & A) == 0);
    V = (fetchedValue >> 6) & 1;
    N = (fetchedValue >> 7) & 1; 
}


///////////////
// ARITHMETIC /
///////////////


void CPU::ADC() {

}

void CPU::SBC() {

} 

void CPU::CMP() {

} 

void CPU::CPX() {

} 

void CPU::CPY() {

}


//////////////////////////////
// INCREMENTS AND DECREMENTS /
//////////////////////////////


void CPU::INC() {
    Mem[fetchAddress]++;
    Z = (Mem[fetchAddress] == 0);
    N = (Mem[fetchAddress] & 0x80) > 0;
} 

void CPU::INX() {
    X++;
    Z = (X == 0);
    N = (X & 0x80) > 0;
} 

void CPU::INY() {
    Y++;
    Z = (Y == 0);
    N = (Y & 0x80) > 0;
} 

void CPU::DEC() {
    Mem[fetchAddress]++;
    Z = (Mem[fetchAddress] == 0);
    N = (Mem[fetchAddress] & 0x80) > 0;
} 

void CPU::DEX() {
    X--;
    Z = (X == 0);
    N = (X & 0x80) > 0;
} 

void CPU::DEY() {
    Y--;
    Z = (Y == 0);
    N = (Y & 0x80) > 0;
}


///////////
// SHIFTS /
///////////


void CPU::ASL() {
    C = (fetchedValue >> 7) & 1;

    Byte Result = fetchedValue << 1;

    if (InstructionTable[currentInstruction].AddressMode == &CPU::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = (Result == 0);
    N = (Result >> 7) & 1;
} 

void CPU::LSR() {
    C = fetchedValue & 1;

    Byte Result = fetchedValue >> 1;

    if (InstructionTable[currentInstruction].AddressMode == &CPU::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = (Result == 0);
    N = 0;
} 

void CPU::ROL() {
    Bit PreviousC = C;
    C = (fetchedValue >> 7) & 1;

    Byte Result = (fetchedValue << 1) | PreviousC;

    if (InstructionTable[currentInstruction].AddressMode == &CPU::IMP) {
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = (Result == 0);
    N = (Result >> 7) & 1;
} 

void CPU::ROR() {
    Bit PreviousC = C;
    C = fetchedValue & 1;

    Byte Result = (fetchedValue >> 1) | (PreviousC << 7);

    if (InstructionTable[currentInstruction].AddressMode == &CPU::IMP) { 
        A = Result;
    }
    else {
        Mem[fetchAddress] = Result;
    }

    Z = (Result == 0); 
    N = PreviousC;
}


////////////////////
// JUMPS AND CALLS /
////////////////////


void CPU::JMP() {} void CPU::JSR() {} void CPU::RTS() {}


/////////////
// BRANCHES /
/////////////


void CPU::BCC() {
    if (C == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BCS() {
    if (C == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BEQ() {
    if (Z == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BMI() {
    if (N == 1) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BNE() {
    if (Z == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BPL() {
    if (N == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BVC() {
    if (V == 0) {
        remainingCycles++;
        fetchAddress = PC + fetchAddressRelative;

        if ((fetchAddress & 0xFF) != (PC & 0xFF)) {
            remainingCycles++;
        }

        PC = fetchAddress;
    }
} 

void CPU::BVS() {
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


void CPU::CLC() {
    C = 0;
} 

void CPU::CLD() {
    D = 0;
} 

void CPU::CLI() {
    I = 0;
} 

void CPU::CLV() {
    V = 0;
} 

void CPU::SEC() {
    C = 1;
} 

void CPU::SED() {
    D = 1;
} 

void CPU::SEI() {
    I = 1;
}


/////////////////////
// SYSTEM FUNCTIONS /
/////////////////////


void CPU::BRK() {} void CPU::NOP() {} void CPU::RTI() {}


////////////////////
// INVALID OP CODE /
////////////////////


void CPU::XXX() {
    Halt = 1;
}