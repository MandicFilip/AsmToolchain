//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_GLOBALSYMBOLMANAGER_H
#define SS_EMULATOR_GLOBALSYMBOLMANAGER_H


#include <string>
#include <vector>
#include "../commonTypes.h"

class GlobalSymbolManager
{
    struct GlobalSymbolInfo {
        std::string symbol;
        uint16_t address;
    };

    std::vector<GlobalSymbolInfo> requestedSymbols;
    std::vector<GlobalSymbolInfo> foundSymbols;

    bool startDefined;
    uint16_t startAddress;

    bool isAlreadyRequested(std::string symbol);
    bool isAlreadyFound(std::string symbol);

    bool isStart(std::string symbol);
public:
    bool checkIfNoneMissing();
    void insertFoundSymbol(std::string symbol, uint16_t address);
    void insertRequestedSymbol(std::string symbol, uint16_t address);
    uint16_t getStartAddress();

    uint16_t getSymbolAddress(std::string symbol);

    void restartManager();

    void debagPrint();
};


#endif //SS_EMULATOR_GLOBALSYMBOLMANAGER_H
