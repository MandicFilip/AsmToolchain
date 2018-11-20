//
// Created by mandula on 2.8.18..
//

#ifndef SS_PROJECT_OPERANDOBJECT_H
#define SS_PROJECT_OPERANDOBJECT_H

#include <string>
#include <cstdint>
#include "../CommonTypes/CommonTypeWrappers.h"


class OperandObject
{
public:
    AddressType type;
    int16_t regNum;
    std::string symbol;
    int16_t numValue;

    OperandObject();

    friend bool operator==(OperandObject& first, OperandObject& second);
    friend bool operator!=(OperandObject& first, OperandObject& second);

    friend std::ostream& operator<<(std::ostream& out, OperandObject& operandObject);
    friend std::istream& operator>>(std::istream& in, OperandObject& operandObject);
};


#endif //SS_PROJECT_OPERANDOBJECT_H
