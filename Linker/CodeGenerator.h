//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_CODEGENERATOR_H
#define SS_EMULATOR_CODEGENERATOR_H


#include "GlobalSymbolManager.h"
#include "LinkerStructs.h"

class CodeGenerator {

    GlobalSymbolManager* globalSymbolManager;
    FileInfo* fileInfo;

    uint16_t getWordFromCodeBuffer(uint16_t position, int bufferNum);
    void setWordInCodeBuffer(uint16_t word, uint16_t position, int bufferNum);
    bool isSymbolGlobal(uint16_t symbolId);

    std::string getSymbolFromId(uint16_t symbolId);
    uint16_t findSymbolAddress(uint16_t symbolId);

    void handleGlobalApsolute(ReallocationInfo &info, int bufferNum);
    void handleSectionApsolute(ReallocationInfo &info, int bufferNum);
    void handleGlobalRelative(ReallocationInfo &info, int bufferNum, uint16_t sectionAddress);
    void handleSectionRelative(ReallocationInfo &info, int bufferNum, uint16_t sectionAddress);

public:
    void fixFileCode(FileInfo* fileInfo, GlobalSymbolManager* globalSymbolManager);
};


#endif //SS_EMULATOR_CODEGENERATOR_H
