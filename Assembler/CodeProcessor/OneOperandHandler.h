//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_ONEOPERANDHANDLER_H
#define SS_PROJECT_ONEOPERANDHANDLER_H


#include "OperandHandler.h"

class OneOperandHandler : public OperandHandler
{
public:

    OneOperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                      SectionTable* sectionTable, CodeGenerator* codeGenerator, ConditionTable* conditionTable);

    void firstPassHandleOperand(LineElements* lineElements) override;

    void secondPassHandleOperand(LineElements* lineElements) override;
};


#endif //SS_PROJECT_ONEOPERANDHANDLER_H
