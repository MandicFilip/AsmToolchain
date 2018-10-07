//
// Created by mandula on 20.8.18..
//

#include "System.h"

System::System()
{
    memory = static_cast<unsigned char *>(calloc(65536, sizeof(unsigned char)));
    for (int i = 0; i < REGISTER_NUMBER; ++i) {
        registers[i] = 0;
    }
    psw = 0;
    registers[6] = STACK_START;

    for (int i = 0; i < INTERRUPTS_NUMBER; ++i) {
        interruptsNotifyTable[i] = false;
    }
    outputIONotify = false;
}

bool System::isReadAllowedFromSection(uint16_t address)
{
    for (std::vector<SegmentInfo>::iterator iter = segmentTable.begin();  iter != segmentTable.end() ; ++iter) {
        if (iter->isAddressInSegment(address)) return iter->isReadAllowed();
    }
    return true;
}

bool System::isWriteAllowedFromSection(uint16_t address)
{
    for (std::vector<SegmentInfo>::iterator iter = segmentTable.begin();  iter != segmentTable.end() ; ++iter) {
        if (iter->isAddressInSegment(address)) return iter->isReadAllowed();
    }
    return true;
    return true;
}

bool System::isExecutionAllowedFromSection(uint16_t address)
{
    for (std::vector<SegmentInfo>::iterator iter = segmentTable.begin();  iter != segmentTable.end() ; ++iter) {
        if (iter->isAddressInSegment(address)) return iter->isReadAllowed();
    }
    return true;
    return true;
}

uint16_t System::readRegister(uint16_t registerNumber)
{
    return registers[registerNumber];
}

void System::writeInRegister(uint16_t registerNumber, uint16_t data)
{
    registers[registerNumber] = data;
}

uint16_t System::readPSW()
{
    return psw;
}

void System::writeInPSW(uint16_t data)
{
    psw = data;
}

uint16_t System::readSP()
{
    return registers[SP_REG];
}

void System::writeInSP(uint16_t data)
{
    registers[SP_REG] = data;
}

void System::incrementSP()
{
    registers[SP_REG]++;
}

void System::decrementSP()
{
    registers[SP_REG]--;
}

uint16_t System::readPCNextWord()
{
    uint16_t tmp = readWordFromMemory(readPC());
    incPC();
    incPC();
    return tmp;
}

uint16_t System::readPC()
{
    return registers[PC_REG];
}

void System::writeInPC(uint16_t data)
{
    registers[PC_REG] = data;
}

void System::incPC()
{
    registers[PC_REG]++;
}

unsigned char System::readByteFromMemory(uint16_t address)
{
    return memory[address];
}

void System::writeByteToMemory(uint16_t address, unsigned char data)
{
    memory[address] = data;
}

uint16_t System::readWordFromMemory(uint16_t address)
{
    unsigned char lower = readByteFromMemory(address++);
    unsigned char higher = readByteFromMemory(address);
    return createWordFromBytes(lower, higher);
}

void System::writeWordToMemory(uint16_t address, uint16_t data)
{
    writeByteToMemory(address++, extractLowerByteFromWord(data));
    writeByteToMemory(address, extractHigherByteFromWord(data));
}

void System::pushByteToStack(unsigned char data)
{
    decrementSP();
    writeByteToMemory(readSP(), data);
}

void System::pushWordToStack(uint16_t data)
{
    pushByteToStack(extractHigherByteFromWord(data));
    pushByteToStack(extractLowerByteFromWord(data));
}

unsigned char System::popByteFromStack()
{
    unsigned char ret = readByteFromMemory(readSP());
    incrementSP();
    return ret;
}

uint16_t System::popWordFromStack()
{
    unsigned char lower = popByteFromStack();
    unsigned char higher = popByteFromStack();
    return createWordFromBytes(lower, higher);
}

uint16_t System::readWordFromInputIO()
{
    return readWordFromMemory(IN_IO_ADDRESS);
}

void System::writeWordToOutputIO(uint16_t data)
{
    writeWordToMemory(OUT_IO_ADDRESS, data);
}

uint16_t System::createWordFromBytes(unsigned char lower, unsigned char higher)
{
    uint16_t ret = higher;
    ret <<= 8;

    ret += lower;
    return ret;
}

unsigned char System::extractLowerByteFromWord(uint16_t word)
{
    return static_cast<unsigned char>(word);
}

unsigned char System::extractHigherByteFromWord(uint16_t word)
{
    return static_cast<unsigned char>(word >> 8);
}

void System::setInterrupt(int entry)
{
    interruptsNotifyTable[entry] = true;
}

void System::resetInterrupt(int entry)
{
    interruptsNotifyTable[entry] = false;
}

bool System::isInterrupt(int entry)
{
    return interruptsNotifyTable[entry];
}
