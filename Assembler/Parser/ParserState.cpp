//
// Created by mandula on 29.7.18..
//

#include "ParserState.h"
#include "ParserErrors/WrongSymbolFoundError.h"
#include "ParserExceptions/doOperandJob.h"

ParserState::ParserState()
{

}

ParserState::~ParserState()
{

}

void ParserState::prepareForNextLine()
{
    labelAllowed = true;
    directiveAllowed = true;
    mnemonicAllowed = true;
    operandAllowed = false;
    directiveInfoAllowed = false;

    commaAllowed = false;
    lineEndAllowed = true;
    lineType = none;
}

void ParserState::labelFound()
{
    if (!labelAllowed) throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Label found."));
    labelAllowed = false;
    lineType = justLabelLine;

}

void ParserState::directiveFound()
{
    if (lineType == mnemonicLine || lineType == labelMnemonicLine) {
        operandFound();
        throw doOperandJob();
    }
    if (!directiveAllowed) throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Directive found."));
    labelAllowed = false;
    directiveAllowed = false;
    mnemonicAllowed = false;

    operandAllowed = false;
    directiveInfoAllowed = true;

    commaAllowed = false;
    lineEndAllowed = true;

    if (lineType == none) lineType = directiveLine;
    else lineType = labelDirectiveLine;
}



void ParserState::mnemonicFound()
{
    if (!mnemonicAllowed)  throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Mnemonic found."));
    labelAllowed = false;
    directiveAllowed = false;
    mnemonicAllowed = false;

    operandAllowed = true;
    directiveInfoAllowed = false;

    commaAllowed = false;
    lineEndAllowed = true;

    if (lineType == none) lineType = mnemonicLine;
    else lineType = labelMnemonicLine;
}

void ParserState::operandFound()
{
    if (!operandAllowed)  throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Operand found."));
    operandAllowed = false;
    commaAllowed = true;
    lineEndAllowed = true;

}

void ParserState::directiveInfoFound()
{
    if (!directiveInfoAllowed)  throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Directive data found."));
    directiveInfoAllowed = false;
    commaAllowed = true;
    lineEndAllowed = true;
}

void ParserState::commaFound()
{
    if (!commaAllowed) throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Comma found."));
    labelAllowed = false;
    directiveAllowed = false;
    mnemonicAllowed = false;

    if ((lineType == directiveLine) || (lineType == labelDirectiveLine)) {
        operandAllowed = false;
        directiveInfoAllowed = true;
    }
    else {
        operandAllowed = true;
        directiveInfoAllowed = false;
    }
    commaAllowed = false;
    lineEndAllowed = false;
}

void ParserState::lineEndFound()
{
    if (!lineEndAllowed)
        throw WrongSymbolFoundError(const_cast<char*>("Syntax error! Line doesn't contains all expected information."));
    prepareForNextLine();
}

LineType ParserState::getLineType() const
{
    return lineType;
}
