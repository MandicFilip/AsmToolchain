//
// Created by mandula on 2.8.18..
//

#ifndef SS_PROJECT_OPERANDMANAGER_H
#define SS_PROJECT_OPERANDMANAGER_H

#include <string>
#include "../TransferObjects/OperandObject.h"
#include "../CommonTypes/CommonTypeWrappers.h"

class OperandParser
{
protected:

    AddressType findOperandType(std::string symbol);

    int16_t getImmValue(std::string symbol);

    std::string getSimValueSymbol(std::string symbol);

    std::string getMemDirSymbol(std::string symbol);

    int16_t getLocFromValue(std::string symbol);

    int16_t getRegNum(std::string symbol);

    int16_t getRegOffsetValue(std::string symbol);

    std::string getRegOffsetSymbol(std::string symbol);

    std::string getPcRelSymbol(std::string symbol);

    bool isPSW(const std::string& symbol) const;

    bool isReg(const std::string& symbol) const;

    int16_t extractNumber(std::string symbol);

    bool isNumber(std::string symbol, long start, long end);
    bool isSymbol(std::string symbol, long start, long end);

public:

    OperandObject* parseOperand(std::string symbol);
};


#endif //SS_PROJECT_OPERANDMANAGER_H
