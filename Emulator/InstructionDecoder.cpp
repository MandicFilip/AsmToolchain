//
// Created by mandula on 22.8.18..
//

#include "InstructionDecoder.h"

InstructionDecoder::InstructionDecoder()
{
    noDstOperandInstructions.push_back(9); //push code
    noDstOperandInstructions.push_back(11); //call code
    noDstOperandInstructions.push_back(12); //iret code

    noSrcOperandInstructions.push_back(10); //pop code
    noSrcOperandInstructions.push_back(12); //iret code
}

void InstructionDecoder::decodeInstruction(uint16_t code, InstructionInfo *info)
{
    info->condition = getCondition(code);
    info->opCode = getOperationCode(code);
    info->dstCode = getDstType(code);
    info->dstReg = getDstRegister(code);
    info->srcCode = getSrcType(code);
    info->srcReg = getSrcRegister(code);
    info->extraWordProperty = isExtraByteRequired(info);
}

unsigned char InstructionDecoder::getCondition(uint16_t code)
{
    uint16_t mask = THREE_BITS_MASK;
    code >>= CONDITION_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::getOperationCode(uint16_t code)
{
    uint16_t mask = FOUR_BITS_MASK;
    code >>= OPERATION_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::getDstType(uint16_t code)
{
    uint16_t mask = TWO_BITS_MASK;
    code >>= DST_TYPE_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::getDstRegister(uint16_t code)
{
    uint16_t mask = THREE_BITS_MASK;
    code >>= DST_REG_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::getSrcType(uint16_t code)
{
    uint16_t mask = TWO_BITS_MASK;
    code >>= SRC_TYPE_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::getSrcRegister(uint16_t code)
{
    uint16_t mask = THREE_BITS_MASK;
    code >>= SRC_REG_SHIFT;
    return static_cast<unsigned char>(mask & code);
}

unsigned char InstructionDecoder::isExtraByteRequired(InstructionInfo *info)
{
    if (isDstOperandNeeded(info)) {
        if (checkOperandForExtraByte(info->dstCode, info->dstReg)) return 1;
    }
    if (isSrcOperandNeeded(info)) {
        if (checkOperandForExtraByte(info->srcCode, info->srcReg)) return 2;
    }
    return 0;
}

bool InstructionDecoder::isSrcOperandNeeded(InstructionInfo *info)
{
    for (std::vector<unsigned char>::iterator iter = noSrcOperandInstructions.begin();
            iter != noSrcOperandInstructions.end(); ++iter) {
        if (info->opCode == *iter) return false;
    }
    return true;
}

bool InstructionDecoder::isDstOperandNeeded(InstructionInfo *info)
{
    for (std::vector<unsigned char>::iterator iter = noDstOperandInstructions.begin();
         iter != noDstOperandInstructions.end(); ++iter) {
        if (info->opCode == *iter) return false;
    }
    return true;
}

bool InstructionDecoder::checkOperandForExtraByte(unsigned char type, unsigned char registerNumber)
{
    if (type == 0) {
        return registerNumber != 7; //code for psw type = imm and reg = 7
    }
    return type != 1; //regdir = 1 has no extra operands
}
