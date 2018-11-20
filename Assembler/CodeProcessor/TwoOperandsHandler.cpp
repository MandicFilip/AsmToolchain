//
// Created by mandula on 11.8.18..
//

#include <algorithm>
#include "TwoOperandsHandler.h"
#include "Exceptions/BadDstOperandException.h"
#include "Exceptions/BadInstructionSizeError.h"
#include "../Tables/MnemonicTable.h"



TwoOperandsHandler::TwoOperandsHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                                       SectionTable* sectionTable, CodeGenerator* codeGenerator,
                                       ConditionTable* conditionTable) : OperandHandler(locationCounterTracer,
                                                                                        symbolTable, sectionTable,
                                                                                        codeGenerator, conditionTable)
{}

void TwoOperandsHandler::firstPassHandleOperand(LineElements* lineElements)
{
    OperandObject* operandObject1 = lineElements->getDst();
    OperandObject* operandObject2 = lineElements->getSrc();

    if (!canBeDstOperand(operandObject1)) throw BadDstOperandException();

    uint16_t op1Size = countAdditionalBytes(operandObject1);
    uint16_t op2Size = countAdditionalBytes(operandObject2);
    if (op1Size + op2Size > 2) throw BadInstructionSizeError();

    locationCounter->moveLocationCounter(BASIC_INSTRUCTION_SIZE + op1Size + op2Size);
}

void TwoOperandsHandler::secondPassHandleOperand(LineElements* lineElements)
{
    std::string opCode = lineElements->getOpCode();
    std::transform(opCode.begin(), opCode.end(), opCode.begin(), ::tolower);

    std::string condition = lineElements->getCondition();
    std::transform(condition.begin(), condition.end(), condition.begin(), ::tolower);

    OperandObject* operand = lineElements->getDst();

    uint16_t code = getOpAndConditionCode(opCode, condition);

    uint16_t operandCode = 0;

    operandCode = getOperandCode(operand);
    code |= (operandCode << shiftDstBits);
    uint16_t extraWord;
    bool hasExtraWord = false;
    if (extraBytesRequired(operand)) {
        if (isSymbolAddress(operand)) extraWord = createReallocationRecord(operand);
        else extraWord = static_cast<uint16_t>(operand->numValue);
        hasExtraWord = true;
        locationCounter->moveLocationCounter(4);
    }

    operand = lineElements->getSrc();
    operandCode = getOperandCode(operand);
    code |= operandCode;
    if (extraBytesRequired(operand)) {
        if (isSymbolAddress(operand)) extraWord = createReallocationRecord(operand);
        else extraWord = static_cast<uint16_t>(operand->numValue);
        hasExtraWord = true;
    }
    if (hasExtraWord) locationCounter->moveLocationCounter(4);
    else locationCounter->moveLocationCounter(2);
    codeGenerator->generateLineOfCode(code, extraWord, hasExtraWord);
}
