//

#include <iostream>
#include <cstring>
#include "LineElements.h"
#include "../Parser/ParserErrors/TooManyOperandsError.h"
#include <cstring>

//
// Created by mandula on 25.7.18..

LineElements::LineElements() : lineType(none), operandNum(0), dst(NULL), src(NULL)
{
    directiveInfo = new std::vector<std::string>;
}



LineElements::~LineElements()
{

    if (dst != NULL) delete(dst);
    if (src != NULL) delete(src);

    directiveInfo->clear();
    if (directiveInfo != NULL) {
        delete (directiveInfo);
        directiveInfo = NULL;
    }
}

LineType LineElements::getLineType() const
{
    return lineType;
}

void LineElements::setLineType(LineType lineType)
{
    LineElements::lineType = lineType;
}

const std::string& LineElements::getLabel() const
{
    return label;
}

void LineElements::setLabel(const std::string& label)
{
    LineElements::label = label;
}

const std::string& LineElements::getDirective() const
{
    return directive;
}

void LineElements::setDirective(const std::string& directive)
{
    LineElements::directive = directive;
}

const std::string& LineElements::getOpCode() const
{
    return opCode;
}

const std::string& LineElements::getCondition() const
{
    return condition;
}

void LineElements::setMnemonic(const std::string& mnemonic)
{
    LineElements::opCode = mnemonic.substr(0, mnemonic.length() - 2);
    LineElements::condition = mnemonic.substr(mnemonic.length() - 2, mnemonic.length());
}


void LineElements::setOperand(OperandObject* operandObject)
{
    if (operandNum++ == 1) {
        dst = src;
    }
    src = operandObject;
    if (operandNum > 2) throw TooManyOperandsError();
}

std::vector<std::string>* LineElements::getDirectiveInfo() const
{
    return directiveInfo;
}

int LineElements::getLineNumber() const
{
    return lineNumber;
}

void LineElements::setLineNumber(int lineNumber)
{
    LineElements::lineNumber = lineNumber;
}

OperandObject* LineElements::getDst() const
{
    return dst;
}

void LineElements::setDst(OperandObject* dst)
{
    LineElements::dst = dst;
}

OperandObject* LineElements::getSrc() const
{
    return src;
}

void LineElements::setSrc(OperandObject* src)
{
    LineElements::src = src;
}

bool operator==(const LineElements& first, const LineElements& second)
{
    if (first.getLineType() != second.getLineType()) return false;

    if(strcmp(first.getLabel().data(), second.getLabel().data())) return false;
    if(strcmp(first.getDirective().data(), second.getDirective().data())) return false;
    if(strcmp(first.getOpCode().data(), second.getOpCode().data())) return false;
    if(strcmp(first.getCondition().data(), second.getCondition().data())) return false;

    if (((first.getDst() == NULL) && (second.getDst() != NULL)) ||
            ((first.getDst() != NULL) && (second.getDst() == NULL)))
        return false;
    if (((first.getSrc() == NULL) && (second.getSrc() != NULL)) ||
        ((first.getSrc() != NULL) && (second.getSrc() == NULL)))
        return false;

    if ((first.getDst() != NULL) && (*first.getDst() != *second.getDst()))
        return false;
    if ((first.getSrc() != NULL) && (*first.getSrc() != *second.getSrc()))
        return false;

    std::vector<std::string>* firstDirectiveInfo = first.getDirectiveInfo();
    std::vector<std::string>* secondDirectiveInfo = second.getDirectiveInfo();

    if(firstDirectiveInfo->size() == secondDirectiveInfo->size());

    std::vector<std::string>::iterator foundIter = firstDirectiveInfo->begin();
    std::vector<std::string>::iterator excpIter = secondDirectiveInfo->begin();
    while(foundIter != firstDirectiveInfo->end()) {
        if(strcmp(foundIter->data(), excpIter->data())) return false;
        ++foundIter;
        ++excpIter;
    }

    return true;
}

bool operator!=(const LineElements& first, const LineElements& second)
{
    return !(first == second);
}

int LineElements::getOperandNum() const
{
    return operandNum;
}
