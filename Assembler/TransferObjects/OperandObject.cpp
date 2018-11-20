
#include <cstring>
#include <iostream>
#include "OperandObject.h"

OperandObject::OperandObject() : type(imm), regNum(-1), numValue(-1), symbol(":")
{}


bool operator==(OperandObject& first, OperandObject& second)
{
    if (first.numValue != second.numValue) return false;
    if (first.regNum != second.regNum) return false;
    if (first.type != second.type) return false;
    return strcmp(first.symbol.data(), second.symbol.data()) == 0;

}

bool operator!=(OperandObject& first, OperandObject& second)
{
    return !(first == second);
}

std::ostream& operator<<(std::ostream& out, OperandObject& operandObject)
{
    out << operandObject.type << " ";
    out << operandObject.regNum << " ";
    out << operandObject.numValue << " ";
    out << operandObject.symbol << std::endl;

}

std::istream& operator>>(std::istream& in, OperandObject& operandObject)
{
    int num;
    in >> num;
    operandObject.type = (AddressType) num;
    in >> operandObject.regNum;
    in >> operandObject.numValue;
    in >> operandObject.symbol;
}
