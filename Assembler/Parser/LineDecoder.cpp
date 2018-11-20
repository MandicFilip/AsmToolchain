//
// Created by mandula on 25.7.18..
//

#include "LineDecoder.h"
#include "ParserExceptions/EndOfFileException.h"
#include "ParserExceptions/LineEndException.h"
#include "ParserErrors/UnknownSymbolFound.h"
#include "ParserErrors/ParserError.h"
#include "ParserErrors/WrongSymbolFoundError.h"
#include "ParserExceptions/doOperandJob.h"
#include <iostream>
#include <fstream>
#include <sstream>

LineDecoder::LineDecoder() : lineCounter(1) {}

LineDecoder::~LineDecoder() {}

void LineDecoder::decodeLine(std::string line, LineElements* lineElements)
{
    if (lineElements == NULL) return;

    this->line = line;
    int wordStartIndex = index;
    prepareToParseNextLine();

    lineElements->setLineNumber(lineCounter);

    while(true) {
        try {
            dropSpaces();
            wordStartIndex = index;
            std::string symbol = getNextSymbol();
            analiseWord(symbol, lineElements);
        } catch (LineEndException e) {
            lineCounter++;
            break;
        } catch (ParserError& e) {
            std::ostringstream fullMessage;
            fullMessage << e.what() << " Line " << lineCounter << ":" << wordStartIndex << "." << std::endl;
            throw ParserError(fullMessage.str().data());
        }
    }
    return;

}

void LineDecoder::prepareToParseNextLine()
{
    parserState.prepareForNextLine();
    index = 0;
}

void LineDecoder::dropSpaces()
{
    while (line[index] == ' ') {
        index++;
        if (index >= line.length()) throw LineEndException();
    }
}

std::string LineDecoder::getNextSymbol()
{
    if (line[index] == '\0') throw LineEndException();
    else {
        int length = getWordLength();
        std::string symbol = line.substr(index - length, length);
        return symbol;
    }
}

int LineDecoder::getWordLength()
{
    int start = index;
    while (isWordPart()) index++;
    if (index == start){
        if (line[index] == ',') index++;
        else throw LineEndException();
    }
    return index - start;
}

bool LineDecoder::isWordPart()
{
    return  line[index] != ' ' && line[index] != ',' && index < line.length();
}

void LineDecoder::analiseWord(std::string symbol, LineElements* lineElements)
{
    if (isSymbolComma(symbol)) {
        parserState.commaFound();
    }
    else if (isSymbolLabel(symbol)) {
        parserState.labelFound();
        symbol = formatLabel(symbol);
        lineElements->setLabel(symbol);
    }
    else if (isSymbolDirective(symbol)) {
        try {
            parserState.directiveFound();
            lineElements->setDirective(symbol);
        } catch (doOperandJob e) {
            OperandObject* op = operandParser.parseOperand(symbol);
            lineElements->setOperand(op);
        }
    }
    else if (isSymbolRegularWord(symbol)) {
        LineType lineType = parserState.getLineType();
        if (lineType == justLabelLine || lineType == none) {
            parserState.mnemonicFound();
            lineElements->setMnemonic(symbol);
        }
        else if ((lineType == mnemonicLine) || (lineType == labelMnemonicLine)) {
            parserState.operandFound();
            OperandObject* op = operandParser.parseOperand(symbol);
            lineElements->setOperand(op);
        }
        else if ((lineType == directiveLine) || (lineType == labelDirectiveLine)) {
            parserState.directiveInfoFound();
            std::vector<std::string>* directiveInfo = lineElements->getDirectiveInfo();
            directiveInfo->push_back(symbol);
        }
    }
    else {
        throw UnknownSymbolFound();
    }

    lineElements->setLineType(parserState.getLineType());
}

bool LineDecoder::isSymbolComma(std::string symbol)
{
    return symbol.length() == 1 && symbol[0] == ',';
}

bool LineDecoder::isSymbolLabel(std::string symbol)
{
    if (symbol[symbol.length() - 1] != ':' || symbol.length() == 1) return false;

    for (int i = 0; i < symbol.length() - 1; ++i) {
        if (symbol[i] == ',' || symbol[i] == '.' || symbol[i] == ':') return false;
    }

    if (!islower(symbol[0]) && !isupper(symbol[0])) return false;

    return true;
}

bool LineDecoder::isSymbolDirective(std::string symbol)
{

    if (symbol[0] != '.' || symbol.length() == 1) return false;

    for (int i = 1; i < symbol.length(); ++i) {
        if (symbol[i] == ',' || symbol[i] == '.' || symbol[i] == ':') return false;
    }

    return true;
}

bool LineDecoder::isSymbolRegularWord(std::string symbol)
{
    for (int i = 0; i < symbol.length(); ++i) {
        if (symbol[i] == ',' || symbol[i] == '.' || symbol[i] == ':') return false;
    }

    return true;
}

std::string LineDecoder::formatLabel(std::string symbol)
{
    symbol.erase(symbol.end() - 1);
    return symbol;
}
