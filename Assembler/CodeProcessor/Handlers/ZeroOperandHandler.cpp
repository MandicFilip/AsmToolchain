//
// Created by mandula on 11.8.18..
//

#include <algorithm>
#include "ZeroOperandHandler.h"
#include "../../Tables/MnemonicTable.h"

ZeroOperandHandler::ZeroOperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                                       SectionTable* sectionTable, CodeGenerator* codeGenerator,
                                       ConditionTable* conditionTable) : OperandHandler(locationCounterTracer,
                                                                                        symbolTable, sectionTable,
                                                                                        codeGenerator, conditionTable)
{}

void ZeroOperandHandler::firstPassHandleOperand(LineElements* lineElements)
{
    locationCounter->moveLocationCounter(SMALL_INSTRUCTION_SIZE);
}

void ZeroOperandHandler::secondPassHandleOperand(LineElements* lineElements)
{
    std::string opCode = lineElements->getOpCode();
    std::transform(opCode.begin(), opCode.end(), opCode.begin(), ::tolower);

    std::string condition = lineElements->getCondition();
    std::transform(condition.begin(), condition.end(), condition.begin(), ::tolower);

    uint16_t code;

    if (!strcmp(opCode.data(), "ret")) {
        code = getOpAndConditionCode("pop", condition);

        uint16_t regdirPCcode = 15; //01 111, 01 - regdir 111 - r7(pc)
        regdirPCcode <<= shiftDstBits;
        code |= regdirPCcode;
    }
    else {
        code = getOpAndConditionCode(opCode, condition);
    }
    codeGenerator->generateLineOfCode(code, 0, false);
    locationCounter->moveLocationCounter(SMALL_INSTRUCTION_SIZE);
}
