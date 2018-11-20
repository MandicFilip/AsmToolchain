//
// Created by mandula on 2.8.18..
//

#ifndef SS_PROJECT_SYMBOLTABLE_H
#define SS_PROJECT_SYMBOLTABLE_H


#include <string>
#include <utility>
#include <vector>
#include <cstdint>
#include <cstring>
#include <fstream>
#include "../CommonTypes/CommonTypeWrappers.h"

class SymbolTable
{
public:

    SymbolTable();

    virtual ~SymbolTable();

    struct SymbolInfo {
        std::string symbol;
        uint16_t symbolId;
        bool global;
        bool defined;
        uint16_t value;
        std::string section;
        uint16_t offset;
        SymbolInfo(std::string _symbol, uint16_t id, bool isGlobal, __int16_t Value,
                   bool Defined, std::string Section = "UND", uint16_t Offset = 0) :
                symbol(std::move(_symbol)), symbolId(id), value(static_cast<uint16_t>(Value)),
                global(isGlobal), defined(Defined), section(Section), offset(Offset) {}

        friend bool operator==(SymbolInfo& first, SymbolInfo& second) {
            if (strcmp(first.symbol.data(), second.symbol.data())) return false;
            if (first.symbolId != second.symbolId) return false;
            if (first.value != second.value) return false;
            if (first.global != second.global) return false;
            if (first.defined != second.defined) return false;
            return true;
        }
    };

    SymbolInfo getSymbol(std::string symbol);
    uint16_t getSize();
    void defineSectionSymbol(std::string symbol, uint16_t value);
    void defineSymbol(std::string symbol, uint16_t value, std::string section = "UND", uint16_t offset = 0);
    void declareGlobalSymbol(std::string symbol);
    void setValueForSymbol(std::string symbol, uint16_t value);

    friend std::ostream& operator<<(std::ostream& out, SymbolTable& symbolTable);
    void printToFile(std::ofstream& out);
protected:
    std::vector<SymbolInfo> symbolTable;
    int idCounter;

    bool isSymbolDefined(std::string symbol);

    bool isSection(std::string section);
};


#endif //SS_PROJECT_SYMBOLTABLE_H
