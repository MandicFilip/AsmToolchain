#include <utility>

//
// Created by mandula on 9.8.18..
//

#include "DirectiveHandler.h"
#include "../Exceptions/EndDirectiveFoundException.h"
#include "../Exceptions/NegativeAlignmentException.h"
#include "../Exceptions/WrongInfoPassedToDirectiveException.h"

const u_int16_t CHAR_SIZE = 1;
const u_int16_t WORD_SIZE = 2;
const u_int16_t LONG_SIZE = 4;


DirectiveHandler::DirectiveHandler(SymbolTable* symbolTable, SectionTable* sectionTable,
                                   LocationCounter* locationCounterTracer, CodeGenerator* codeGenerator) :
        symbolTable(symbolTable), sectionTable(sectionTable), locationCounter(locationCounterTracer), codeGenerator(codeGenerator)
{}

void DirectiveHandler::handleFirstPass(LineElements* lineElements)
{
    const std::string& directive = lineElements->getDirective();
    if (isSymbolSection(directive)) {
        if (!lineElements->getDirectiveInfo()->empty()) throw WrongInfoPassedToDirectiveException();
        sectionTable->insertSection(directive, locationCounter->getLocationCounter());
        symbolTable->defineSectionSymbol(lineElements->getDirective(), locationCounter->getLocationCounter());
        return;
    }
    if (isSymbolEnd(directive)) {
        if (!lineElements->getDirectiveInfo()->empty()) throw WrongInfoPassedToDirectiveException();
        throw EndDirectiveFoundException();
    }

    if (!strcmp(directive.data(), ".global")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if (info->empty()) throw WrongInfoPassedToDirectiveException();
        for (auto& iter : *info) {
            if (!isSymbol(iter)) throw WrongInfoPassedToDirectiveException();
            symbolTable->declareGlobalSymbol(iter);
        }

    }
    else if (!strcmp(directive.data(), ".align")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if ((info->size() != 1) || !isNumber(info->front(), 0, info->front().length()))
            throw WrongInfoPassedToDirectiveException();

        std::string strValue = info->front();
        int16_t exp = static_cast<int16_t>(calcValue(strValue));

        if (exp < 0) throw NegativeAlignmentException();
        uint16_t alignment = 1;
        for (int i = 0; i < exp; ++i) {
            alignment *= 2;
        }
        locationCounter->align(alignment);
    }
    else if (!strcmp(directive.data(), ".skip")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if ((info->size() != 1) || !isNumber(info->front(), 0, info->front().length()))
            throw WrongInfoPassedToDirectiveException();

        std::string strValue = info->front();
        uint16_t offset = static_cast<uint16_t>(calcValue(strValue));
        locationCounter->moveLocationCounter(offset);
    }
    else if (!strcmp(directive.data(), ".char")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if (info->size() != 1) throw WrongInfoPassedToDirectiveException();
        locationCounter->moveLocationCounter(CHAR_SIZE);
    }
    else if (!strcmp(directive.data(), ".word")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if (info->size() != 1) throw WrongInfoPassedToDirectiveException();
        locationCounter->moveLocationCounter(WORD_SIZE);
    }
    else if (!strcmp(directive.data(), ".long")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        if (info->size() != 1) throw WrongInfoPassedToDirectiveException();
        locationCounter->moveLocationCounter(LONG_SIZE);
    }
    else throw WrongInfoPassedToDirectiveException();
}

void DirectiveHandler::handleSecondPass(LineElements* lineElements)
{
    const std::string& directive = lineElements->getDirective();
    if (isSymbolSection(directive)) {
        codeGenerator->changeSection(directive);
        sectionTable->enterNextSection();
    }
    if (isSymbolEnd(directive)) {

        throw EndDirectiveFoundException();
    }

    if (!strcmp(directive.data(), ".global")) {

    }
    else if (!strcmp(directive.data(), ".align")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        std::string strValue = info->front();
        int16_t exp = static_cast<int16_t>(calcValue(strValue));

        if (exp < 0) throw NegativeAlignmentException();
        uint16_t alignment = 1;
        for (int i = 0; i < exp; ++i) {
            alignment *= 2;
        }
        locationCounter->align(alignment);

        if (!strcmp(sectionTable->getCurrentSection().data(), "UND")) {
            for (int i = 0; i < alignment / 2; ++i) {
                codeGenerator->generateWord(0); //0 - dummy data
            }
        }
    }
    else if (!strcmp(directive.data(), ".skip")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        std::string strValue = info->front();
        uint16_t offset = static_cast<uint16_t>(calcValue(strValue));
        locationCounter->moveLocationCounter(offset);

        for (int i = 0; i < offset; ++i) {
            codeGenerator->generateByte(0); //0 - dummy data
        }
    }
    else if (!strcmp(directive.data(), ".char")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        char numValue;
        std::string strValue = info->front();

        if (isNumber(strValue, 0, strValue.length())) {
            numValue = static_cast<char>(calcValue(strValue));
        }
        else {
            std::string symbol = info->front();
            if (isSymbol(symbol)) {
                numValue = static_cast<char>(handleSymbolForMemoryInitialization(symbol));
            }
            else throw WrongInfoPassedToDirectiveException();
        }
        codeGenerator->generateByte(numValue);
        locationCounter->moveLocationCounter(1);
    }
    else if (!strcmp(directive.data(), ".word")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();
        int16_t numValue;
        std::string strValue = info->front();

        if (isNumber(strValue, 0, strValue.length())) {
            numValue = static_cast<int16_t>(calcValue(strValue));
        }
        else {
            std::string symbol = info->front();
            if (isSymbol(symbol)) {
                numValue = handleSymbolForMemoryInitialization(symbol);
            }
            else throw WrongInfoPassedToDirectiveException();
        }
        codeGenerator->generateWord(numValue);
        locationCounter->moveLocationCounter(2);
    }
    else if (!strcmp(directive.data(), ".long")) {
        std::vector<std::string>* info = lineElements->getDirectiveInfo();

        std::string strValue = info->front();
        int32_t numValue;

        if (isNumber(strValue, 0, strValue.length())) {
            numValue = static_cast<int16_t>(calcValue(strValue));
        }
        else {
            std::string symbol = info->front();
            if (isSymbol(symbol)) {
                numValue = handleSymbolForMemoryInitialization(symbol);
            }
            else throw WrongInfoPassedToDirectiveException();
        }
        codeGenerator->generateLong(numValue);
        locationCounter->moveLocationCounter(4);
    }
}

bool DirectiveHandler::isSymbolSection(std::string symbol)
{
    return !strcmp(symbol.data(), ".text") || !strcmp(symbol.data(), ".data") ||
           !strcmp(symbol.data(), ".rodata") || !strcmp(symbol.data(), ".bss");
}

bool DirectiveHandler::isSymbolEnd(std::string symbol)
{
    return !strcmp(symbol.data(), ".end");
}

int32_t DirectiveHandler::calcValue(std::string symbol)
{
    bool isDec = true;

    int16_t sign = 1;
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

    int32_t ret = 0;
    if (isDec) {
        ret = static_cast<uint16_t>(strtol(symbol.data(), NULL, 10));
    }
    else {
        ret = static_cast<uint16_t>(strtol(symbol.data(), NULL, 16)); //base = 16
    }
    return sign * ret;
}

bool DirectiveHandler::isNumber(std::string symbol, long start, long end)
{
    bool isDec = true;
    if (symbol[start] == '+' || symbol[start] == '-')
    {
        symbol.erase(symbol.begin());
        end--;
    }
    if ((symbol[start] == '0') && ((symbol[start + 1] == 'x') || (symbol[start + 1] == 'X'))) {
        isDec = false;
        symbol.erase(static_cast<unsigned long>(start), 2);
        end -=2;
    }

    if (symbol[end - 1] == 'h' || symbol[end - 1] == 'H') {
        isDec = false;
        symbol.erase(static_cast<unsigned long>(end - 1), 1);
        end--;
    }

    for (int i = static_cast<int>(start); i < end; ++i) {
        if (!isdigit(symbol[i]) && isDec) return false;
        if (!isxdigit(symbol[i]) && !isDec) return false;
    }
    return true;
}

bool DirectiveHandler::isSymbol(std::string symbol, long start, long end)
{
    if (!isupper(symbol[start]) && !islower(symbol[start]) && (symbol[start] != '.')) return false;
    for (int i = static_cast<int>(start); i < end; ++i) {
        if ((i == start) && (symbol[i] == '.')) continue;
        if (!(isdigit(symbol[i]) || isupper(symbol[i]) || islower(symbol[i]))) return false;
    }
    return true;
}

uint16_t DirectiveHandler::handleSymbolForMemoryInitialization(std::string symbol)
{
    SymbolTable::SymbolInfo symbolInfo = symbolTable->getSymbol(std::move(symbol));
    uint16_t numValue;
    uint16_t symbolToBound;
    if (symbolInfo.global) {
        numValue = 0;
        symbolToBound = static_cast<uint16_t>(symbolInfo.symbolId);
    }
    else {
        std::string tmpSection = symbolInfo.section;
        tmpSection.insert(0, ".");
        numValue = symbolInfo.value - sectionTable->getSectionStartAddress(tmpSection);
        symbolToBound = sectionTable->getSectionId(tmpSection);
    }

    codeGenerator->generateReallocationRecord(absolutely, symbolToBound);
    return numValue;
}
