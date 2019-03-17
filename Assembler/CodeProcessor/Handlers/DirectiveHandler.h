//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_DIRECTIVEHANDLER_H
#define SS_PROJECT_DIRECTIVEHANDLER_H


#include "../../TransferObjects/LineElements.h"
#include "../../Tables/SymbolTable.h"
#include "../../Tables/SectionTable.h"
#include "../LocationCounter.h"
#include "../CodeGenerator.h"

class DirectiveHandler
{
protected:
    CodeGenerator* codeGenerator;
    SymbolTable* symbolTable;
    SectionTable* sectionTable;
    LocationCounter* locationCounter;

    bool isSymbolSection(std::string symbol);
    bool isSymbolEnd(std::string symbol);

    int32_t calcValue(std::string symbol);
    bool isNumber(std::string symbol, long start = 0, long end = 0);
    bool isSymbol(std::string symbol, long start = 0, long end = 0);

    uint16_t handleSymbolForMemoryInitialization(std::string symbol);

public:
    DirectiveHandler(SymbolTable* symbolTable, SectionTable* sectionTable,
                     LocationCounter* locationCounterTracer, CodeGenerator* codeGenerator);

    void handleFirstPass(LineElements* lineElements);
    void handleSecondPass(LineElements* lineElements);
};


#endif //SS_PROJECT_DIRECTIVEHANDLER_H
