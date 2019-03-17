//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_TWOOPERANDSHANDLER_H
#define SS_PROJECT_TWOOPERANDSHANDLER_H


#include "../../TransferObjects/OperandObject.h"
#include "OperandHandler.h"

class TwoOperandsHandler : public OperandHandler
{
    uint16_t MAX_INSTRUCTION_SIZE = 4;
public:

    TwoOperandsHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                       SectionTable* sectionTable, CodeGenerator* codeGenerator, ConditionTable* conditionTable);

    void firstPassHandleOperand(LineElements* lineElements) override;

    void secondPassHandleOperand(LineElements* lineElements) override;
};


#endif //SS_PROJECT_TWOOPERANDSHANDLER_H
