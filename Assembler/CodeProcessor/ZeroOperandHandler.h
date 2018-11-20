//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_ZEROOPERANDHANDLER_H
#define SS_PROJECT_ZEROOPERANDHANDLER_H


#include "OperandHandler.h"

class ZeroOperandHandler : public OperandHandler
{
public:

    ZeroOperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                       SectionTable* sectionTable, CodeGenerator* codeGenerator, ConditionTable* conditionTable);

    void firstPassHandleOperand(LineElements* lineElements) override;

    void secondPassHandleOperand(LineElements* lineElements) override;
};


#endif //SS_PROJECT_ZEROOPERANDHANDLER_H
