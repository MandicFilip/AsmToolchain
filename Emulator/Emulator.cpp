//
// Created by mandula on 20.8.18..
//

#include <iostream>
#include "Emulator.h"

Emulator::Emulator(System *system) : operandDecoder(system), operationExecuter(system),
    interruptHandler(system), system(system), isProgramEnd(false)
{}

void Emulator::loopIteration()
{
    fetchInstruction();
    loadOperands();
    executeOperation();
    handleInterrupts();
    if (system->readPC() == 0xFFFF) isProgramEnd = true;
}

void Emulator::fetchInstruction()
{
    uint16_t firstWord = system->readPCNextWord();
    instructionDecoder.decodeInstruction(firstWord, info);
    if (info->extraWordProperty > 0) info->extraWord = system->readPCNextWord();
}

void Emulator::loadOperands()
{
    operandDecoder.fetchOperands(info);
}

void Emulator::executeOperation()
{
    try {
        operationExecuter.executeInstruction(info);
    }
    catch (MyException e) {
        system->setInterrupt(system->ILLEGAL_INSTRUCTION_ROUTINE);
        interruptHandler.setInstruction_error();
    }

}

void Emulator::handleInterrupts()
{
    interruptHandler.handleInterrupt();
}

void Emulator::emulateProgram(ProgramInput *)
{
    if (system->isInterrupt(system->INIT_ROUTINE)) {
        interruptHandler.goToInterrupt(system->INIT_ROUTINE);
        system->resetInterrupt(system->INIT_ROUTINE);
    }
    while (!isProgramEnd) {
        info = new InstructionInfo();
        loopIteration();
        delete(info);
    }
    std::cout << std::endl << "Program executed!" << std::endl;
}
