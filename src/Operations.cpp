#include "CPU.hpp"

// OPERATIONS

//////////////////////////////
// LOAD AND STORE OPERATIONS /
//////////////////////////////


void CPU::LDA() {
    A = fetchedValue;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDX() {} void CPU::LDY() {} void CPU::STA() {} void CPU::STX() {} void CPU::STY() {}


///////////////////////
// REGISTER TRANSFERS /
///////////////////////


void CPU::TAX() {} void CPU::TAY() {} void CPU::TXA() {} void CPU::TYA() {}


/////////////////////
// STACK OPERATIONS /
/////////////////////


void CPU::TSX() {} void CPU::TXS() {} void CPU::PHA() {} void CPU::PHP() {} void CPU::PLA() {} void CPU::PLP() {}


////////////
// LOGICAL /
////////////


void CPU::AND() {
    A = A & fetchedValue;
    Z = (A == 0);
    N = (A & 0x80) > 0;
}

void CPU::EOR() {} void CPU::ORA() {} void CPU::BIT() {}


///////////////
// ARITHMETIC /
///////////////


void CPU::ADC() {

}

void CPU::SBC() {} void CPU::CMP() {} void CPU::CPX() {} void CPU::CPY() {}


//////////////////////////////
// INCREMENTS AND DECREMENTS /
//////////////////////////////


void CPU::INC() {} void CPU::INX() {} void CPU::INY() {} void CPU::DEC() {} void CPU::DEX() {} void CPU::DEY() {}

///////////
// SHIFTS /
///////////



void CPU::ASL() {} void CPU::LSR() {} void CPU::ROL() {} void CPU::ROR() {}


////////////////////
// JUMPS AND CALLS /
////////////////////


void CPU::JMP() {} void CPU::JSR() {} void CPU::RTS() {}


/////////////
// BRANCHES /
/////////////


void CPU::BCC() {} void CPU::BCS() {} void CPU::BEQ() {} void CPU::BMI() {} void CPU::BNE() {} void CPU::BPL() {} void CPU::BVC() {} void CPU::BVS() {} 


////////////////////////
// STATUS FLAG CHANGES /
////////////////////////


void CPU::CLC() {} void CPU::CLD() {} void CPU::CLI() {} void CPU::CLV() {} void CPU::SEC() {} void CPU::SED() {} void CPU::SEI() {}


/////////////////////
// SYSTEM FUNCTIONS /
/////////////////////


void CPU::BRK() {}
void CPU::NOP() {}
void CPU::RTI() {}


////////////////////
// INVALID OP CODE /
////////////////////


void CPU::XXX() {}