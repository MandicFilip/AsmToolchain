//
// Created by mandula on 12.8.18..
//

#ifndef SS_PROJECT_CODEGENERATOR_H
#define SS_PROJECT_CODEGENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "../CommonTypes/CommonTypeWrappers.h"
#include "../Tables/SymbolTable.h"
#include "../Tables/SectionTable.h"

class CodeGenerator
{
    const static int MAX_NUMBER_OF_SECTIONS = 4;
    int currentSection;
    int numberOfSections;

    std::string sections[MAX_NUMBER_OF_SECTIONS];

    std::stringstream reallocationStreams[MAX_NUMBER_OF_SECTIONS];
    std::stringstream codeStreams[MAX_NUMBER_OF_SECTIONS];

    struct ReallocationInfo {
        uint16_t position;
        uint16_t type;
        uint16_t symbolId;
    };

    std::vector<ReallocationInfo> reallocationTable[4];

    std::ofstream* objFileStream;

    uint16_t sectionCounter;
public:
    CodeGenerator();
    virtual ~CodeGenerator();

    void createProgramTextFile(char* file, SymbolTable* symbolTable, SectionTable* sectionTable, uint16_t startAddress);
    void createProgramObjFile(char* file, SymbolTable* symbolTable, SectionTable* sectionTable, uint16_t startAddress);
    void generateReallocationRecord(ReallocationType reallocationType, uint16_t symbolId);
    void generateLineOfCode(uint16_t opCode, uint16_t value, bool hasExtraBytes);
    void generateByte(char byteToGenerate);
    void generateWord(int16_t wordToGenerate);
    void generateLong(int32_t longToGenerate);
    void changeSection(std::string section);
    void generateReallocationRecordForExtraBytes(ReallocationType reallocationType, uint16_t symbolId);
};


#endif //SS_PROJECT_CODEGENERATOR_H
