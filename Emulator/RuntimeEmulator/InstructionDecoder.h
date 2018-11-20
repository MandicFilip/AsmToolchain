//
// Created by mandula on 22.8.18..
//

#ifndef SS_EMULATOR_INSTRUCTIONDECODER_H
#define SS_EMULATOR_INSTRUCTIONDECODER_H


#include "InstructionInfo.h"
#include <vector>

class InstructionDecoder
{
    const uint16_t TWO_BITS_MASK = 3;
    const uint16_t THREE_BITS_MASK = 7;
    const uint16_t FOUR_BITS_MASK = 15;

    const uint16_t CONDITION_SHIFT = 14;
    const uint16_t OPERATION_SHIFT = 10;
    const uint16_t DST_TYPE_SHIFT = 8;
    const uint16_t DST_REG_SHIFT = 5;
    const uint16_t SRC_TYPE_SHIFT = 3;
    const uint16_t SRC_REG_SHIFT = 0;

    std::vector<unsigned char> noDstOperandInstructions;
    std::vector<unsigned char> noSrcOperandInstructions;

    unsigned char getCondition(uint16_t code);
    unsigned char getOperationCode(uint16_t code);
    unsigned char getDstType(uint16_t code);
    unsigned char getDstRegister(uint16_t code);
    unsigned char getSrcType(uint16_t code);
    unsigned char getSrcRegister(uint16_t code);

    unsigned char isExtraByteRequired(InstructionInfo* info);

    bool isSrcOperandNeeded(InstructionInfo* info);
    bool isDstOperandNeeded(InstructionInfo* info);

    bool checkOperandForExtraByte(unsigned char type, unsigned char registerNumber);
public:
    InstructionDecoder();

    void decodeInstruction(uint16_t  code, InstructionInfo* info);
};


#endif //SS_EMULATOR_INSTRUCTIONDECODER_H
