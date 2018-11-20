//
// Created by mandula on 22.8.18..
//

#ifndef SS_EMULATOR_INSTRUCTIONINFORMATION_H
#define SS_EMULATOR_INSTRUCTIONINFORMATION_H


#include "../commonTypes.h"

struct InstructionInfo
{
    unsigned char condition;
    unsigned char opCode;
    unsigned char dstCode;
    unsigned char dstReg;
    unsigned char srcCode;
    unsigned char srcReg;
    uint16_t  extraWord;
    uint16_t operandPlace;
    unsigned char extraWordProperty; //0 - no extra byte, 1 - dst has extra byte, 2 - source has extra byte

    InstructionInfo()
    {
        condition = 0;
        opCode = 0;
        dstCode = 0;
        dstReg = 0;
        srcCode = 0;
        srcReg = 0;
        extraWord = 0;
        operandPlace = 0;
        extraWordProperty = 0;
    }
};


#endif //SS_EMULATOR_INSTRUCTIONINFORMATION_H
