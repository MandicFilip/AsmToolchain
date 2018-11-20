//
// Created by mandula on 22.8.18..
//

#ifndef SS_EMULATOR_OPERANDDECODER_H
#define SS_EMULATOR_OPERANDDECODER_H


#include "../System/System.h"
#include "InstructionInfo.h"

class OperandDecoder
{
    System* system;

public:
    OperandDecoder(System *system);

    void fetchOperands(InstructionInfo* info);
};


#endif //SS_EMULATOR_OPERANDDECODER_H
