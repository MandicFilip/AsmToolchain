//
// Created by mandula on 25.7.18..
//

#include "Parser.h"
#include "ParserExceptions/EndOfFileException.h"
#include "ParserErrors/FileNotFoundError.h"
#include "ParserErrors/UnknownSymbolFound.h"
#include "ParserErrors/ParserError.h"
#include <sstream>
#include <string>

Parser::Parser()
{

}

Parser::Parser(char* filePath) : fileInput(filePath)
{
    if (!fileInput.is_open()) {
        throw FileNotFoundError(filePath);
    }
}

void Parser::reopenFile(char* filePath)
{
    if (fileInput.is_open()) fileInput.close();
    fileInput.open(filePath);
    if (!fileInput.is_open()) {
        throw FileNotFoundError(filePath);
    }
}

Parser::~Parser()
{
    if (fileInput.is_open()) fileInput.close();
}

std::string Parser::readLine()
{
    std::string line;
    if (std::getline(fileInput, line)) {
        return line;
    }
    else throw EndOfFileException();
}

void Parser::parseLine(LineElements* lineElements)
{
    while (true) {
        std::string line = readLine();
        lineDecoder.decodeLine(line, lineElements);
        if (lineElements->getLineType() != none) return;
    }
}
