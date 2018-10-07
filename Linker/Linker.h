//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_LINKER_H
#define SS_EMULATOR_LINKER_H


#include <string>
#include <vector>
#include "../commonTypes.h"
#include "ObjFileReader.h"
#include "CodeGenerator.h"
#include "SectionManager.h"
#include "../TransferObjects/ProgramInput.h"

class Linker
{

    ObjFileReader objFileReader;

    std::string* fileNames;
    int fileNumber;

    CodeGenerator codeGenerator;
    SectionManager sectionManager;
    GlobalSymbolManager globalSymbolManager;

    ProgramInput* programInput;

    void handleFirstPass();
    void doBetweenPasses();
    void handleSecondPass();

    void addSections(FileInfo* fileInfo);
    void addGlobalSymbols(FileInfo* fileInfo);

    void fillProgramInfo(FileInfo* fileInfo);

    void debagPrint(FileInfo& fileInfo);
public:
    void linkFiles(std::string* fileNames, int fileNum, ProgramInput* programInput);

    void print(FileInfo info);
};


#endif //SS_EMULATOR_LINKER_H
