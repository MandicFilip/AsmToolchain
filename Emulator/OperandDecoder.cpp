//
// Created by mandula on 22.8.18..
//

#include "OperandDecoder.h"

OperandDecoder::OperandDecoder(System *system) : system(system)
{}

void OperandDecoder::fetchOperands(InstructionInfo *info)
{
    if (info->extraWordProperty == 0) return;

    unsigned char type = 0;
    unsigned char registerNumber = 0;

    if (info->extraWordProperty == 1) {
        type = info->dstCode;
        registerNumber = info->dstReg;
    }
    else {
        type = info->srcCode;
        registerNumber = info->srcReg;
    }

    if (type == 0) return; //immed - operand is built in instruction code

    if (type == 2) { //memdir
        info->operandPlace = system->readWordFromMemory(info->extraWord);
    }
    else { //regindpom
        int16_t address = system->readRegister(registerNumber);
        address += info->extraWord;
        info->operandPlace = system->readWordFromMemory(address);
        info->extraWord = address;
    }
}
