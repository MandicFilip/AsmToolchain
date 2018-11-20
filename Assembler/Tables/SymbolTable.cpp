//
// Created by mandula on 2.8.18..
//

#include <cstring>
#include <iostream>
#include <sstream>
#include "SymbolTable.h"
#include "Exceptions/MissingSymbolException.h"
#include "Exceptions/SymbolAlreadyDefinedException.h"

SymbolTable::SymbolTable() : idCounter(1)
{
    SymbolInfo info("UND", 0, false, 0, true, "UND", 0);
    symbolTable.insert(symbolTable.begin(), info);
}

SymbolTable::~SymbolTable()
{
    symbolTable.clear();
}

SymbolTable::SymbolInfo SymbolTable::getSymbol(std::string symbol)
{
    for (std::vector<SymbolInfo>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if (iter->symbol == symbol) return *iter;
    }
    throw MissingSymbolException();
}

void SymbolTable::defineSymbol(std::string symbol, uint16_t value, std::string section, uint16_t offset)
{
    if (isSymbolDefined(symbol)) throw SymbolAlreadyDefinedException();

    if (strcmp(section.data(), "UND")) section.erase(0, 1);

    bool globalSymbol = false;
    int pos = 0;
    for (std::vector<SymbolInfo>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) {
            pos = iter - symbolTable.begin();
            globalSymbol = true;
        }
    }
    if (globalSymbol) {
        symbolTable[pos].defined = true;
        symbolTable[pos].value = value;
        symbolTable[pos].section = section;
        symbolTable[pos].offset = offset;
    }
    else {
        SymbolInfo info(symbol, idCounter++, false, value, true, section, offset);
        symbolTable.push_back(info);
    }

}

void SymbolTable::declareGlobalSymbol(std::string symbol)
{
    if (isSymbolDefined(symbol)) throw SymbolAlreadyDefinedException();

    SymbolInfo info(symbol, idCounter++, true, 0, false);
    symbolTable.push_back(info);
}

void SymbolTable::setValueForSymbol(std::string symbol, uint16_t value)
{
    if (!isSymbolDefined(symbol)) throw MissingSymbolException();

    for (std::vector<SymbolInfo>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) {
            iter->value = value;
        }
    }
}

bool SymbolTable::isSymbolDefined(std::string symbol)
{
    for (std::vector<SymbolInfo>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) {
            if (iter->defined) return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, SymbolTable& symbolTable)
{
    out << std::endl;
    out << "---Symbol Table---" << std::endl;
    out << "Symbol   " << "Id   " << "Global   " << "Defined    " << "Value   " << "Section    " << "Offset" << std::endl;

    for (std::vector<SymbolTable::SymbolInfo>::iterator iter = symbolTable.symbolTable.begin();
         iter != symbolTable.symbolTable.end(); ++iter) {
        unsigned long blank = 0;
        out << iter->symbol;
        blank = 9 - iter->symbol.length();
        for (int i = 0; i < blank; i++) out << " ";

        std::ostringstream ss1;
        ss1 << std::hex << iter->symbolId;
        std::string str1 = ss1.str();
        out << str1;
        blank = 5 - str1.length();
        for (int i = 0; i < blank; i++) out << " ";

        out << std::hex << iter->global << "        "; //8 spaces
        out << std::hex << iter->defined << "          "; //9 spaces

        std::ostringstream ss2;
        ss2 << std::hex << iter->value;
        std::string str2 = ss2.str();
        out << str2;
        blank = 8 - str2.length();
        for (int i = 0; i < blank; i++) out << " ";

        out << iter->section;
        blank = 11 - iter->section.length();
        for (int i = 0; i < blank; i++) out << " ";

        out << std::hex << iter->offset;

        out << std::endl;
    }
    out << std::endl;

    return out;
}

void SymbolTable::defineSectionSymbol(std::string symbol, uint16_t value)
{
    int place = 0;
    for (std::vector<SymbolInfo>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if (isSection(iter->symbol)) place++;
        else iter->symbolId++;
    }
    std::string section = symbol;
    section.erase(0, 1);
    SymbolInfo info(symbol, place, false, value, true, section);
    symbolTable.insert(symbolTable.begin() + place, info);
    idCounter++;
}

bool SymbolTable::isSection(std::string section)
{
    return !strcmp(section.data(), ".text") || !strcmp(section.data(), ".data") ||
           !strcmp(section.data(), ".rodata") || !strcmp(section.data(), ".bss") || (!strcmp(section.data(), "UND"));
}

void SymbolTable::printToFile(std::ofstream& out)
{
    for (int i = 1; i < symbolTable.size(); ++i) {
        uint16_t symbolSize = static_cast<uint16_t>(symbolTable[i].symbol.size());
        uint16_t sectionSize = static_cast<uint16_t>(symbolTable[i].section.size());

        out.write(reinterpret_cast<const char*>(&symbolSize), sizeof(uint16_t));
        out.write(symbolTable[i].symbol.data(), symbolSize);

        out.write(reinterpret_cast<const char*>(&symbolTable[i].symbolId), sizeof(uint16_t));
        out.write(reinterpret_cast<const char*>(&symbolTable[i].global), sizeof(uint16_t));
        out.write(reinterpret_cast<const char*>(&symbolTable[i].value), sizeof(uint16_t));
        out.write(reinterpret_cast<const char*>(&symbolTable[i].defined), sizeof(uint16_t));

        out.write(reinterpret_cast<const char*>(&sectionSize), sizeof(uint16_t));
        out.write(symbolTable[i].section.data(), sectionSize);

        out.write(reinterpret_cast<const char*>(&symbolTable[i].offset), sizeof(uint16_t));
    }

}

uint16_t SymbolTable::getSize()
{
    return static_cast<uint16_t>(symbolTable.size());
}
