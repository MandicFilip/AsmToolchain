//
// Created by mandula on 9.8.18..
//

#include "OperandHandler.h"
#include "../Tables/MnemonicTable.h"

OperandHandler::OperandHandler(LocationCounter* locationCounterTracer, SymbolTable* symbolTable,
                               SectionTable* sectionTable, CodeGenerator* codeGenerator, ConditionTable* conditionTable)
        : locationCounter(locationCounterTracer), symbolTable(symbolTable), sectionTable(sectionTable),
          codeGenerator(codeGenerator), conditionTable(conditionTable)
{}

uint16_t OperandHandler::countAdditionalBytes(OperandObject* operandObject)
{
    if (operandObject->type == regDir || operandObject->type == psw) return 0;
    else return 2;
}

bool OperandHandler::canBeDstOperand(OperandObject* operandObject)
{
    return true;
    //return !(operandObject->type == imm || operandObject->type == symValue);
}

void OperandHandler::setMnemonicTable(MnemonicTable* mnemonicTable)
{
    OperandHandler::mnemonicTable = mnemonicTable;
}

uint16_t OperandHandler::getOpAndConditionCode(std::string opCode, std::string condition)
{
    uint16_t ret = 0;

    uint16_t tmp;

    tmp = conditionTable->getConditionCode(condition);
    ret |= (tmp << shiftConditionBits);

    tmp = mnemonicTable->getMnemonicCode(opCode);
    ret |= (tmp << shiftOpCodeBits);

    return ret;
}

uint16_t OperandHandler::createReallocationRecord(OperandObject* operand)
{
    uint16_t wordSize = 2;

    AddressType type = operand->type;
    int16_t codeValue = 0;
    uint16_t symbolId;
    if (type == pcRel) {
        SymbolTable::SymbolInfo symbolInfo = symbolTable->getSymbol(operand->symbol);
        std::string tmpSection = symbolInfo.section;
        tmpSection.insert(0, ".");

        if (symbolInfo.global) {
            codeValue -= wordSize;
            symbolId = symbolInfo.symbolId;
        } else {
            codeValue = symbolInfo.offset - wordSize;
            symbolId = sectionTable->getSectionId(tmpSection);
        }

        if (strcmp(tmpSection.data(), sectionTable->getCurrentSection().data())) {
            codeGenerator->generateReallocationRecordForExtraBytes(relative, symbolId);
        }
        else {
            codeValue = static_cast<int16_t>(sectionTable->getSectionStartAddress(tmpSection) + symbolInfo.offset -
                                              locationCounter->getLocationCounter() - 4);
        }
    }
    else {
        SymbolTable::SymbolInfo symbolInfo = symbolTable->getSymbol(operand->symbol);
        std::string tmpSection = symbolInfo.section;
        tmpSection.insert(0, ".");

        if (symbolInfo.global) {
            symbolId = symbolInfo.symbolId;
        }
        else {
            codeValue = symbolInfo.offset;
            symbolId = sectionTable->getSectionId(tmpSection);
        }
        codeGenerator->generateReallocationRecordForExtraBytes(absolutely, symbolId);
    }
    return static_cast<uint16_t>(codeValue);
}

bool OperandHandler::isSymbolAddress(OperandObject* operand)
{
    AddressType type = operand->type;
    return type == symValue || type == memDir || type == regIndBySym || type == pcRel;
}

uint16_t OperandHandler::getOperandCode(OperandObject* operand)
{
    uint16_t operandCode = 0;
    AddressType type = operand->type;

    if (type == regDir) operandCode = 1;
    else if (type == memDir || type == locFromValue) operandCode = 2;
    else if (type == regIndBySym || type == regIndByValue || type == pcRel) operandCode = 3;
    operandCode <<= 3;

    if (type == psw || type == pcRel) operandCode += 7;
    else if (type == regIndBySym || type == regIndByValue || type == regDir) operandCode += operand->regNum;

    return operandCode;
}

bool OperandHandler::extraBytesRequired(OperandObject* operand)
{
    AddressType type = operand->type;
    return !((type == psw) || ((type == regDir)));
}
