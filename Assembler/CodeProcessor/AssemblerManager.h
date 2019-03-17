//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_ASSEMBLYMANAGER_H
#define SS_PROJECT_ASSEMBLYMANAGER_H


#include "../Parser/Parser.h"
#include "../Tables/SymbolTable.h"
#include "LocationCounter.h"
#include "../Tables/SectionTable.h"
#include "../Tables/MnemonicTable.h"
#include "../Tables/ConditionTable.h"
#include "Handlers/LabelHandler.h"
#include "Handlers/DirectiveHandler.h"
#include "CodeGenerator.h"

class AssemblerManager
{
protected:
    Parser* parser;
    SymbolTable* symbolTable;
    SectionTable* sectionTable;
    MnemonicTable* mnemonicTable;
    ConditionTable* conditionTable;
    LocationCounter* locationCounter;

    LabelHandler* labelHandler;
    DirectiveHandler* directiveHandler;
    ZeroOperandHandler* zeroOperandHandler;
    OneOperandHandler* oneOperandHandler;
    TwoOperandsHandler* twoOperandsHandler;

    CodeGenerator* codeGenerator;
    char* fileName;

    uint16_t startAddress;

    void initialize(char* filePath, int locationCounterStart);
    void doOnePass(int passNum);
    void firstPassWork(LineElements* lineElements);
    void doBetweenPasses();
    void secondPassWork(LineElements* lineElements);
    void writeInFile();

public:
    AssemblerManager();

    virtual ~AssemblerManager();

    void assemblyFile(char* filePath, int locationCounterStart);

    void terminate();

    void resolveLabelFirstPass(LineElements* lineElements);

    void resolveDirectiveFirstPass(LineElements* lineElements);

    void resolveMnemonicFirstPass(LineElements* lineElements);
};


#endif //SS_PROJECT_ASSEMBLYMANAGER_H
