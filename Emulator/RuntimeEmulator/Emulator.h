//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_EMULATOR_H
#define SS_EMULATOR_EMULATOR_H


#include "../System/System.h"
#include "../TransferObjects/ProgramInput.h"
#include "InstructionDecoder.h"
#include "OperandDecoder.h"
#include "OperationExecuter.h"
#include "InterruptHandler.h"

class Emulator
{
    System* system;
    bool isProgramEnd;
public:
    Emulator(System *system);

private:
    InstructionDecoder instructionDecoder;
    OperandDecoder operandDecoder;
    OperationExecuter operationExecuter;
    InterruptHandler interruptHandler;

    InstructionInfo* info;

    void loopIteration();
    void fetchInstruction();
    void loadOperands();
    void executeOperation();
    void handleInterrupts();

public:
    void emulateProgram(ProgramInput*);
};


#endif //SS_EMULATOR_EMULATOR_H
