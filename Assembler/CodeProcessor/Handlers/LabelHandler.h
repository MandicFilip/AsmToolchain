//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_LABELHANDLER_H
#define SS_PROJECT_LABELHANDLER_H


#include <string>
#include "../../CommonTypes/CommonTypeWrappers.h"
#include "../../Tables/SymbolTable.h"
#include "../LocationCounter.h"
#include "../../Tables/SectionTable.h"

class LabelHandler
{
    SymbolTable* symbolTable;
    SectionTable* sectionTable;
    LocationCounter* locationCounter;
public:
    LabelHandler(SymbolTable* symbolTable, SectionTable* sectionTable, LocationCounter* locationCounter);

    virtual ~LabelHandler();

    void handleLabel(std::string symbol);
};


#endif //SS_PROJECT_LABELHANDLER_H
