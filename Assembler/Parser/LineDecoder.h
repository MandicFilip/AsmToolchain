//
// Created by mandula on 25.7.18..
//

#ifndef SS_PROJECT_LINEDECODER_H
#define SS_PROJECT_LINEDECODER_H


#include "../TransferObjects/LineElements.h"
#include "ParserState.h"
#include <string>
#include "OperandParser.h"

class LineDecoder
{

protected:

    OperandParser operandParser;

    int lineCounter;

    int index;
    std::string line;
    ParserState parserState;

    void prepareToParseNextLine();
    void dropSpaces();
    std::string getNextSymbol();

    int getWordLength();
    bool isWordPart();

    void analiseWord(std::string symbol, LineElements* lineElements);

    bool isSymbolComma(std::string symbol);
    bool isSymbolLabel(std::string symbol);
    bool isSymbolDirective(std::string symbol);
    bool isSymbolRegularWord(std::string symbol);

    std::string formatLabel(std::string symbol);
public:
    LineDecoder();
    ~LineDecoder();

    void decodeLine(std::string line, LineElements* lineElements);
};


#endif //SS_PROJECT_LINEDECODER_H
