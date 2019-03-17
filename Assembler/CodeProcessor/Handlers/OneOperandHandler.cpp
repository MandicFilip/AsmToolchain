//
// Created by mandula on 11.8.18..
//

#include <algorithm>
#include "OneOperandHandler.h"
#include "../Exceptions/BadDstOperandException.h"
#include "../../Tables/MnemonicTable.h"

OneOperandHandler::OneOperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                                     SectionTable* sectionTable, CodeGenerator* codeGenerator,
                                     ConditionTable* conditionTable) : OperandHandler(locationCounterTracer,
                                                                                      symbolTable, sectionTable,
                                                                                      codeGenerator, conditionTable)
{}

void OneOperandHandler::firstPassHandleOperand(LineElements* lineElements)
{
    OperandObject* operandObject;
    operandObject = lineElements->getSrc();

    if (!strcmp(lineElements->getOpCode().data(), "pop")) {
        if (!canBeDstOperand(operandObject)) throw BadDstOperandException();
    }

    uint16_t opSize = countAdditionalBytes(operandObject);
    locationCounter->moveLocationCounter(BASIC_INSTRUCTION_SIZE + opSize);
}

void OneOperandHandler::secondPassHandleOperand(LineElements* lineElements)
{
    std::string opCode = lineElements->getOpCode();
    std::transform(opCode.begin(), opCode.end(), opCode.begin(), ::tolower);

    std::string condition = lineElements->getCondition();
    std::transform(condition.begin(), condition.end(), condition.begin(), ::tolower);

    OperandObject* operand;

    if (!strcmp(opCode.data(), "jmp")) {
        uint16_t code;
        operand = lineElements->getSrc();
        if (operand->type == pcRel) code = getOpAndConditionCode("add", condition);
        else {
            code = getOpAndConditionCode("mov", condition);
        }

        uint16_t operandCode = 1;
        operandCode <<= 3;
        operandCode += 7;

        code |= (operandCode << shiftDstBits);

        operandCode = getOperandCode(lineElements->getSrc());
        code |= operandCode;

        uint16_t extraWord = 0;
        bool hasExtraWord = false;
        if (areExtraBytesRequired((lineElements->getSrc()))) {
            if (isSymbolAddress(operand)) extraWord = createReallocationRecord(operand);
            else extraWord = static_cast<uint16_t>(operand->numValue);
            hasExtraWord = true;
            locationCounter->moveLocationCounter(LARGE_INSTRUCTION_SIZE);
        }
        else locationCounter->moveLocationCounter(SMALL_INSTRUCTION_SIZE);
        codeGenerator->generateLineOfCode(code, extraWord, hasExtraWord);
    }
    else {
        uint16_t code = getOpAndConditionCode(opCode, condition);

        unsigned shiftSize = 0;
        operand = lineElements->getSrc();
        if (!strcmp(opCode.data(), "pop")) {
            shiftSize = shiftDstBits;
        }

        uint16_t mask = getOperandCode(operand);
        code |= (mask << shiftSize);

        bool hasExtraWord = false;
        uint16_t extraWord = 0;
        if (areExtraBytesRequired(operand)) {
            if (isSymbolAddress(operand)) extraWord = createReallocationRecord(operand);
            else extraWord = static_cast<uint16_t>(operand->numValue);
            hasExtraWord = true;
            locationCounter->moveLocationCounter(LARGE_INSTRUCTION_SIZE);
        }
        else locationCounter->moveLocationCounter(SMALL_INSTRUCTION_SIZE);
        codeGenerator->generateLineOfCode(code, extraWord, hasExtraWord);
    }

}
