//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_SYSTEM_H
#define SS_EMULATOR_SYSTEM_H


#include <vector>
#include "../commonTypes.h"

struct System
{
    const static int REGISTER_NUMBER = 8;
    const static uint16_t OUT_IO_ADDRESS = 0xfffe;
    const static uint16_t IN_IO_ADDRESS = 0xfffc;
    const static int PC_REG = 7;
    const static int SP_REG = 6;

    const static int INTERRUPTS_NUMBER = 8;

    const static int INIT_ROUTINE = 0;
    const static int TIMER_ROUTINE = 1;
    const static int ILLEGAL_INSTRUCTION_ROUTINE = 2;
    const static int INPUT_ROUTINE = 3;
    const static int INTERRUPT_PSW_BIT = 15;
    const static int TIMER_PSW_BIT = 13;

    const static int TIMER_PERIOD = 1;

    unsigned char* memory;
    uint16_t psw;
    uint16_t registers[8];

    bool interruptsNotifyTable[8];
    bool outputIONotify;

    struct SegmentInfo {
        uint16_t descriptor;
        uint16_t startAddress;
        uint16_t size;

        bool isReadAllowed()
        {
            return static_cast<bool>(descriptor & 4);
        }
        bool isWriteAllowed()
        {
            return static_cast<bool>(descriptor & 2);
        }
        bool isExecuteAllowed()
        {
            return static_cast<bool>(descriptor & 1);
        }

        bool isAddressInSegment(uint16_t address)
        {
            return (address >= startAddress) && (address < startAddress + size);
        }
    };

    System();

    void setInterrupt(int entry);
    void resetInterrupt(int entry);
    bool isInterrupt(int entry);

    bool isReadAllowedFromSection(uint16_t address);
    bool isWriteAllowedFromSection(uint16_t address);
    bool isExecutionAllowedFromSection(uint16_t address);

    uint16_t readRegister(uint16_t registerNumber);
    void writeInRegister(uint16_t registerNumber, uint16_t data);

    uint16_t readPSW();
    void writeInPSW(uint16_t data);

    uint16_t readSP();
    void writeInSP(uint16_t data);
    void incrementSP();
    void decrementSP();

    uint16_t readPC();
    void writeInPC(uint16_t data);
    uint16_t readPCNextWord();
    void incPC();

    unsigned char readByteFromMemory(uint16_t address);
    void writeByteToMemory(uint16_t address, unsigned char  data);

    uint16_t readWordFromMemory(uint16_t address);
    void writeWordToMemory(uint16_t address, uint16_t data);

    void pushByteToStack(unsigned char data);
    void pushWordToStack(uint16_t data);
    unsigned char popByteFromStack();
    uint16_t popWordFromStack();

    uint16_t readWordFromInputIO();
    void writeWordToOutputIO(uint16_t data);

    uint16_t createWordFromBytes(unsigned char lower, unsigned char higher);
    unsigned char extractLowerByteFromWord(uint16_t word);
    unsigned char extractHigherByteFromWord(uint16_t word);

    std::vector<SegmentInfo> segmentTable;

};


#endif //SS_EMULATOR_SYSTEM_H
