//
// Created by mandula on 25.7.18..
//

#ifndef SS_PROJECT_LINEELEMENTS_H
#define SS_PROJECT_LINEELEMENTS_H

#include <string>
#include <vector>
#include "OperandObject.h"
#include <iostream>


class LineElements
{
    int operandNum;

    int lineNumber;
    LineType lineType;

    std::string label;

    std::string directive;
    std::string opCode;
    std::string condition;

    OperandObject* dst;
    OperandObject* src;

    std::vector<std::string>* directiveInfo;

public:
    LineElements();
    ~LineElements();

    LineType getLineType() const;
    void setLineType(LineType lineType);

    const std::string& getLabel() const;
    void setLabel(const std::string& label);

    const std::string& getDirective() const;
    void setDirective(const std::string& directive);

    const std::string& getOpCode() const;
    const std::string& getCondition() const;
    void setMnemonic(const std::string& mnemonic);

    OperandObject* getDst() const;
    void setDst(OperandObject* dst);

    OperandObject* getSrc() const;
    void setSrc(OperandObject* src);

    void setOperand(OperandObject* operandObject);

    std::vector<std::string>* getDirectiveInfo() const;

    int getLineNumber() const;
    void setLineNumber(int lineNumber);

    int getOperandNum() const;

    friend bool operator==(const LineElements& first, const LineElements& second);
    friend bool operator!=(const LineElements& first, const LineElements& second);
};


#endif //SS_PROJECT_LINEELEMENTS_H
