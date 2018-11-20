//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_LINKERSTRUCTS_H
#define SS_EMULATOR_LINKERSTRUCTS_H


#include <string>
#include <vector>
#include "../commonTypes.h"

const int MAX_SECTION_NUMBER = 4;

struct SectionInfo
{
    std::string section;
    uint16_t startAddress;
    uint16_t size;
    uint16_t descriptor;
};

struct SymbolInfo
{
    std::string symbol;
    uint16_t symbolId;
    bool global;
    bool defined;
    uint16_t value;
    std::string section;
    uint16_t offset;
};

struct ReallocationInfo
{
    uint16_t place;
    uint16_t reallocationType;
    uint16_t symbolToBound;
};

struct FileInfo
{
    uint16_t startPosition;
    uint16_t sectionsNumber;
    uint16_t symbolsNumber;

    SectionInfo sections[MAX_SECTION_NUMBER];
    std::vector<SymbolInfo> symbols;
    std::vector<ReallocationInfo> reallocationRecordSections[MAX_SECTION_NUMBER];
    std::vector<unsigned char> codeBuffer[MAX_SECTION_NUMBER];

};

#endif //SS_EMULATOR_LINKERSTRUCTS_H
