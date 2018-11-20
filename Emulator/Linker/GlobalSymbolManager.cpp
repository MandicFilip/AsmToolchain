//
// Created by mandula on 19.8.18..
//

#include <iostream>
#include <iomanip>
#include "GlobalSymbolManager.h"
#include "Exceptions/GlobalSymbolAlreadyFound.h"
#include "Exceptions/SymbolNotExists.h"
#include "Exceptions/StartSymbolMissing.h"

bool GlobalSymbolManager::checkIfNoneMissing() {
    return !requestedSymbols.size();
}

void GlobalSymbolManager::insertFoundSymbol(std::string symbol, uint16_t address) {
    if (isAlreadyFound(symbol)) throw GlobalSymbolAlreadyFound(const_cast<char*>(symbol.data()));

    GlobalSymbolInfo globalSymbolInfo;
    globalSymbolInfo.symbol = symbol;
    globalSymbolInfo.address = address;

    foundSymbols.push_back(globalSymbolInfo);

    std::vector<GlobalSymbolInfo>::iterator position;
    bool isRequested = false;
    for (std::vector<GlobalSymbolInfo>::iterator iter = requestedSymbols.begin();
         iter != requestedSymbols.end() ; ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) {
            position = iter;
            isRequested = true;
            break;
        }
    }

    if (isStart(symbol)) {
        startAddress = address;
        startDefined = true;
    }

    if (isRequested) requestedSymbols.erase(position);
}

void GlobalSymbolManager::insertRequestedSymbol(std::string symbol, uint16_t address) {
    if (isAlreadyRequested(symbol)) return;
    if (isAlreadyFound(symbol)) return;

    GlobalSymbolInfo globalSymbolInfo;
    globalSymbolInfo.symbol = symbol;
    globalSymbolInfo.address = address;

    requestedSymbols.push_back(globalSymbolInfo);
}

uint16_t GlobalSymbolManager::getStartAddress() {
    if (startDefined) return startAddress;
    throw StartSymbolMissing();
}

bool GlobalSymbolManager::isStart(std::string symbol) {
    return !strcmp(symbol.data(), "START");
}

bool GlobalSymbolManager::isAlreadyRequested(std::string symbol) {
    for (std::vector<GlobalSymbolInfo>::iterator iter = requestedSymbols.begin();
    iter != requestedSymbols.end() ; ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) return true;
    }
    return false;
}

bool GlobalSymbolManager::isAlreadyFound(std::string symbol) {
    for (std::vector<GlobalSymbolInfo>::iterator iter = foundSymbols.begin();
         iter != foundSymbols.end() ; ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) return true;
    }
    return false;
}

uint16_t GlobalSymbolManager::getSymbolAddress(std::string symbol)
{
    for (std::vector<GlobalSymbolInfo>::iterator iter = foundSymbols.begin();
         iter != foundSymbols.end() ; ++iter) {
        if (!strcmp(symbol.data(), iter->symbol.data())) return iter->address;
    }
    throw SymbolNotExists(symbol);
}

void GlobalSymbolManager::restartManager()
{
    startAddress = 0;
    startDefined = false;
    requestedSymbols.clear();
    foundSymbols.clear();
}

void GlobalSymbolManager::debagPrint()
{
    std::cout << "Found table" << std::endl;
    for (std::vector<GlobalSymbolInfo>::iterator iter = foundSymbols.begin();
         iter != foundSymbols.end() ; ++iter) {
        std::cout << iter->symbol << " " <<
            std::hex << std::setw(2) << std::setfill('0') << iter->address << std::endl;
    }

    std::cout << "Request table" << std::endl;
    for (std::vector<GlobalSymbolInfo>::iterator iter = requestedSymbols.begin();
         iter != requestedSymbols.end() ; ++iter) {
        std::cout << iter->symbol << " " <<
                  std::hex << std::setw(2) << std::setfill('0') << iter->address << std::endl;
    }
}
