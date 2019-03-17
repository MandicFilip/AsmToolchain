//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_OPERANDHANDLER_H
#define SS_PROJECT_OPERANDHANDLER_H


#include "../../TransferObjects/LineElements.h"
#include "../LocationCounter.h"
#include "../../Tables/SectionTable.h"
#include "../../Tables/SymbolTable.h"
#include "../CodeGenerator.h"
#include "../../Tables/ConditionTable.h"

const u_int16_t SMALL_INSTRUCTION_SIZE = 2;
const u_int16_t LARGE_INSTRUCTION_SIZE = 4;

class MnemonicTable;

class OperandHandler
{
protected:
    uint16_t BASIC_INSTRUCTION_SIZE = 2;
    LocationCounter* locationCounter;
    MnemonicTable* mnemonicTable;
    SectionTable* sectionTable;
    SymbolTable* symbolTable;
    CodeGenerator* codeGenerator;
    ConditionTable* conditionTable;

    uint16_t shiftConditionBits = 14;
    uint16_t shiftOpCodeBits = 10;
    uint16_t shiftDstBits = 5;

    uint16_t countAdditionalBytes(OperandObject* operandObject);
    bool canBeDstOperand(OperandObject* operandObject);
public:

    OperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                   SectionTable* sectionTable, CodeGenerator* codeGenerator, ConditionTable* conditionTable);

    void setMnemonicTable(MnemonicTable* mnemonicTable);

    virtual void firstPassHandleOperand(LineElements* lineElements) = 0;
    virtual void secondPassHandleOperand(LineElements* lineElements) = 0;

    uint16_t getOpAndConditionCode(std::string opCode, std::string condition);

    uint16_t createReallocationRecord(OperandObject* operand);
    bool isSymbolAddress(OperandObject* operand);

    uint16_t getOperandCode(OperandObject* operand);
    bool areExtraBytesRequired(OperandObject* operand);
};


#endif //SS_PROJECT_OPERANDHANDLER_H
