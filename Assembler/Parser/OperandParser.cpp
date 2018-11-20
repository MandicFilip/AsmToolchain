//
// Created by mandula on 2.8.18..
//

#include "OperandParser.h"
#include "ParserErrors/BadOperandError.h"

//enum AddressType {imm, symValue, memDir, locFromValue, regDir, regIndByValue, regIndBySym, pcRel};

AddressType OperandParser::findOperandType(std::string symbol)
{
    if (symbol == "") throw BadOperandError(const_cast<char*>(symbol.data()));

    if (symbol[0] == '&') {
        if (isSymbol(symbol, 1, symbol.length())) return symValue;
    }
    else if (symbol[0] == '*') {
        if (isNumber(symbol, 1, symbol.length())) return locFromValue;
    }
    else if (symbol[0] == '$') {
        if (isSymbol(symbol, 1, symbol.length())) return pcRel;
    }
    else if (isReg(symbol)) {

        if (symbol.size() == 2) return regDir;

        if (symbol[2] == '[' && symbol[symbol.length() - 1] == ']') {
            if (isNumber(symbol, 3, symbol.length() - 1)) return regIndByValue;

            if (isSymbol(symbol, 3, symbol.length() - 1)) return regIndBySym;
        }

    }
    else if (isPSW(symbol)) {
        return psw;
    }
    else if (islower(symbol[0]) || isupper(symbol[0]) || (symbol[0] == '.')) {
        if (isSymbol(symbol, 0, symbol.length())) return memDir;
    }
    else if (isNumber(symbol, 0, symbol.length())) {
        return imm;
    }

    throw BadOperandError(const_cast<char*>(symbol.data()));
}

bool OperandParser::isReg(const std::string& symbol) const
{
    return ((symbol[0] == 'r' || symbol[0] == 'R') && isdigit(symbol[1]) && symbol[1] < '8') ||
           ((symbol[0] == 'p' || symbol[0] == 'P') && (symbol[1] == 'c' || symbol[1] == 'C')) ||
           ((symbol[0] == 's' || symbol[0] == 'S') && (symbol[1] == 'p' || symbol[1] == 'P'));
}

bool OperandParser::isPSW(const std::string& symbol) const
{
    return (symbol[0] == 'p' || symbol[0] == 'P') &&
           (symbol[1] == 's' || symbol[1] == 'S') &&
           (symbol[2] == 'w' || symbol[2] == 'W') &&
           (symbol.length() == 3);
}

bool OperandParser::isNumber(std::string symbol, long start, long end)
{
    bool isDec = true;
    if (symbol[start] == '+' || symbol[start] == '-')
    {
        symbol.erase(symbol.begin());
        end--;
    }
    if ((symbol[start] == '0') && ((symbol[start + 1] == 'x') || (symbol[start + 1] == 'X'))) {
        isDec = false;
        symbol.erase(start, 2);
        end -=2;
    }

    if (symbol[end - 1] == 'h' || symbol[end - 1] == 'H') {
        isDec = false;
        symbol.erase(end - 1, 1);
        end--;
    }

    for (int i = start; i < end; ++i) {
        if (!isdigit(symbol[i]) && isDec) return false;
        if (!isxdigit(symbol[i]) && !isDec) return false;
    }
    return true;
}

bool OperandParser::isSymbol(std::string symbol, long start, long end)
{
    if (!isupper(symbol[start]) && !islower(symbol[start]) && (symbol[start] != '.')) return false;
    for (int i = start; i < end; ++i) {
        if ((i == start) && (symbol[i] == '.')) continue;
        if (!(isdigit(symbol[i]) || isupper(symbol[i]) || islower(symbol[i]))) return false;
    }
    return true;
}

int16_t OperandParser::getImmValue(std::string symbol)
{
    return extractNumber(symbol);
}

std::string OperandParser::getSimValueSymbol(std::string symbol)
{
    symbol.erase(symbol.begin());
    return symbol;
}

std::string OperandParser::getMemDirSymbol(std::string symbol)
{
    return symbol;
}

int16_t OperandParser::getLocFromValue(std::string symbol)
{
    symbol.erase(symbol.begin());
    return extractNumber(symbol);
}

int16_t OperandParser::getRegNum(std::string symbol)
{
    if (((symbol[0] == 'p' || symbol[0] == 'P') && (symbol[1] == 'c' || symbol[1] == 'C'))) return 7; //pc = r7

    if (((symbol[0] == 's' || symbol[0] == 'S') && (symbol[1] == 'p' || symbol[1] == 'P'))) return 6; //sp = r6

    return symbol[1] - '0';
}

int16_t OperandParser::getRegOffsetValue(std::string symbol)
{
    std::string subSymbol = symbol.substr(3, symbol.length() - 4);
    return extractNumber(subSymbol);
}

std::string OperandParser::getRegOffsetSymbol(std::string symbol)
{
    return symbol.substr(3, symbol.length() - 4);
}

std::string OperandParser::getPcRelSymbol(std::string symbol)
{
    symbol.erase(symbol.begin());
    return symbol;
}

OperandObject* OperandParser::parseOperand(std::string symbol)
{
    AddressType type = findOperandType(symbol);

    OperandObject* op = new OperandObject();
    op->type = type;
    switch (type) {
        case imm:
            op->numValue = getImmValue(symbol);
            break;
        case symValue:
            op->symbol = getSimValueSymbol(symbol);
            break;
        case memDir:
            op->symbol = getMemDirSymbol(symbol);
            break;
        case locFromValue:
            op->numValue = getLocFromValue(symbol);
            break;
        case regDir:
            op->regNum = getRegNum(symbol);
            break;
        case regIndByValue:
            op->regNum = getRegNum(symbol);
            op->numValue = getRegOffsetValue(symbol);
            break;
        case regIndBySym:
            op->regNum = getRegNum(symbol);
            op->symbol = getRegOffsetSymbol(symbol);
            break;
        case pcRel:
            op->symbol = getPcRelSymbol(symbol);
            break;
        default:
            break;
    } //no case for psw, its hard coded

    return op;
}

int16_t OperandParser::extractNumber(std::string symbol)
{
    int16_t sign = 1;
    bool isDec = true;
    if (symbol[0] == '+') symbol.erase(symbol.begin());
    if (symbol[0] == '-') {
        sign = -1;
        symbol.erase(symbol.begin());
    }
    if ((symbol[0] == '0') && ((symbol[0 + 1] == 'x') || (symbol[0 + 1] == 'X'))) {
        isDec = false;
        symbol.erase(0, 2);
    }

    if (symbol[symbol.length() - 1] == 'h' || symbol[symbol.length() - 1] == 'H') {
        isDec = false;
        symbol.erase(symbol.length() - 1, 1);
    }

    int16_t ret = 0;
    if (isDec) {
        ret = static_cast<int16_t>(atoi(symbol.data()));
    }
    else {
        ret = static_cast<int16_t>(strtol(symbol.data(), NULL, 16));
    }
    return sign * ret;
}
