//
// Created by mandula on 9.8.18..
//

#include "LabelHandler.h"
#include "../Exceptions/LabelDefinedInNoneSectionException.h"

LabelHandler::LabelHandler(SymbolTable* symbolTable, SectionTable* sectionTable, LocationCounter* locationCounter) :
        symbolTable(symbolTable), sectionTable(sectionTable), locationCounter(locationCounter)
{}

LabelHandler::~LabelHandler()
{
    symbolTable = NULL;
    locationCounter = NULL;
}

void LabelHandler::handleLabel(std::string symbol)
{
    std::string section = sectionTable->getCurrentSection();
    if (!strcmp(section.data(), "none")) throw LabelDefinedInNoneSectionException();
    uint16_t offset = locationCounter->getLocationCounter() - sectionTable->getSectionStartAddress(section);
    symbolTable->defineSymbol(symbol, locationCounter->getLocationCounter(), section, offset);
}
