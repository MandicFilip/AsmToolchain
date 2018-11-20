//
// Created by mandula on 12.8.18..
//

#include "CodeGenerator.h"
#include "Exceptions/FailToCreateObjFileException.h"
#include "../Tables/SymbolTable.h"
#include <iomanip>

CodeGenerator::CodeGenerator() : currentSection(-1), numberOfSections(0), sectionCounter(0)
{
    for (int i = 0; i < MAX_NUMBER_OF_SECTIONS; ++i) {
        sections[i] = "UND";
    }
}

CodeGenerator::~CodeGenerator()
{
    if (objFileStream != NULL) {
        if (objFileStream->is_open()) objFileStream->close();
        if (objFileStream != NULL) delete(objFileStream);
    }
}

void CodeGenerator::createProgramTextFile
        (char* file, SymbolTable* symbolTable, SectionTable* sectionTable, uint16_t startAddress)
{
    objFileStream = new std::ofstream(file);
    if (!objFileStream->is_open()) throw FailToCreateObjFileException();

    *objFileStream << std::hex << startAddress << " ";
    *objFileStream << std::hex << numberOfSections << " ";
    *objFileStream << std::hex << symbolTable->getSize() << std::endl;

    for (int i = 0; i < numberOfSections; ++i) {
        *objFileStream << sections[i] << " ";
        *objFileStream << std::hex << sectionTable->getSectionStartAddress(sections[i]) << " ";
        *objFileStream << std::hex << sectionTable->getSectionSize(sections[i]) << " ";
        *objFileStream << sectionTable->getSectionDescriptor(sections[i]) << std::endl;
    }

    *objFileStream << *symbolTable;

    for (int i = 0; i < numberOfSections; ++i) {
        std::string str = reallocationStreams[i].str();

        if (!strcmp(sections[i].data(), ".bss")) continue;

        *objFileStream << "#ret" << sections[i] << std::endl;
        int j = 0;
        while (str.length() > 0) {
            unsigned char position1 = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << std::hex << std::setw(2) << std::setfill('0') << unsigned(position1);
            unsigned char position2 = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << std::hex << std::setw(2) << std::setfill('0') << unsigned(position2);
            *objFileStream << " ";

            unsigned char reallocationType = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            if (reallocationType == absolutely) *objFileStream << "absolutely ";
            else *objFileStream << "relative ";

            unsigned char symbol1 = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << std::hex << std::setw(2) << std::setfill('0') << unsigned(symbol1);
            unsigned char symbol2 = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << std::hex << std::setw(2) << std::setfill('0') << unsigned(symbol2);
            *objFileStream << " ";

            *objFileStream << std::endl;
        }
        *objFileStream << std::endl;
    }

    for (int i = 0; i < numberOfSections; ++i) {
        std::string str = codeStreams[i].str();

        if (!strcmp(sections[i].data(), ".bss")) continue;

        *objFileStream << "#" << sections[i] << std::endl;
        int j = 0;
        while (str.length() > 0) {
            unsigned char c = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << std::hex << std::setw(2) << std::setfill('0') << unsigned(c);
            *objFileStream << " ";
            j++;
            if (j == 12) {
                j = 0;
                *objFileStream << std::endl;
            }
        }
        *objFileStream << std::endl;
    }
    objFileStream->close();
    delete(objFileStream);
    objFileStream = NULL;
}

void CodeGenerator::createProgramObjFile(char* file, SymbolTable* symbolTable, SectionTable* sectionTable,
                                         uint16_t startAddress)
{
    objFileStream = new std::ofstream(file, std::ios::binary);
    if (!objFileStream->is_open()) throw FailToCreateObjFileException();

    uint16_t symbolTableSize = symbolTable->getSize();

    objFileStream->write(reinterpret_cast<const char*>(&startAddress), sizeof(uint16_t));
    objFileStream->write(reinterpret_cast<const char*>(&numberOfSections), sizeof(uint16_t));
    objFileStream->write(reinterpret_cast<const char*>(&symbolTableSize), sizeof(uint16_t));

    for (int i = 0; i < numberOfSections; ++i) {
        uint16_t stringSize = static_cast<uint16_t>(sections[i].size());
        uint16_t sectionStart = sectionTable->getSectionStartAddress(sections[i]);
        uint16_t sectionSize = sectionTable->getSectionSize(sections[i]);
        uint16_t sectionDescriptor =  sectionTable->getSectionDescriptor(sections[i]);

        objFileStream->write(reinterpret_cast<const char*>(&stringSize), sizeof(uint16_t));
        objFileStream->write(sections[i].data(), stringSize);
        objFileStream->write(reinterpret_cast<const char*>(&sectionStart), sizeof(uint16_t));
        objFileStream->write(reinterpret_cast<const char*>(&sectionSize), sizeof(uint16_t));
        objFileStream->write(reinterpret_cast<const char*>(&sectionDescriptor), sizeof(uint16_t));
    }

    symbolTable->printToFile(*objFileStream);

    for (int i = 0; i < numberOfSections; ++i) {

        if (!strcmp(sections[i].data(), ".bss")) continue;
        uint16_t tmp = static_cast<uint16_t>(reallocationTable[i].size());
        objFileStream->write(reinterpret_cast<const char*>(&tmp), sizeof(uint16_t));
        for (std::vector<ReallocationInfo>::iterator iter = reallocationTable[i].begin();
                iter != reallocationTable[i].end();++iter) {
            objFileStream->write(reinterpret_cast<const char*>(&iter->position), sizeof(uint16_t));
            uint16_t tmpReallocationType = 0;
            if (iter->type == relative) tmpReallocationType = 1;
            objFileStream->write(reinterpret_cast<const char*>(&tmpReallocationType), sizeof(uint16_t));
            objFileStream->write(reinterpret_cast<const char*>(&iter->symbolId), sizeof(uint16_t));
        }
    }
    for (int i = 0; i < numberOfSections; ++i) {
        std::string str = codeStreams[i].str();

        if (!strcmp(sections[i].data(), ".bss")) continue;

        while (str.size() > 0) {
            unsigned char c = static_cast<unsigned char>(str[0]);
            str.erase(0, 1);
            *objFileStream << c;
        }
    }
    objFileStream->close();
    delete(objFileStream);
    objFileStream = NULL;
}

void CodeGenerator::generateReallocationRecord(ReallocationType reallocationType, uint16_t symbolId)
{
    unsigned char half = static_cast<unsigned char>(sectionCounter >> 8);
    reallocationStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(sectionCounter);
    reallocationStreams[currentSection] << std::hex << half;

    half = static_cast<unsigned char>(reallocationType);
    reallocationStreams[currentSection] << std::hex << half;

    half = static_cast<unsigned char>(symbolId >> 8);
    reallocationStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(symbolId);
    reallocationStreams[currentSection] << std::hex << half;

    ReallocationInfo tmp;
    tmp.position = sectionCounter;
    tmp.type = reallocationType;
    tmp.symbolId = symbolId;
    reallocationTable[currentSection].push_back(tmp);
}

void CodeGenerator::generateReallocationRecordForExtraBytes(ReallocationType reallocationType, uint16_t symbolId)
{
    sectionCounter += 2;
    generateReallocationRecord(reallocationType, symbolId);
    sectionCounter -= 2;
}

void CodeGenerator::generateLineOfCode(uint16_t opCode, uint16_t value, bool hasExtraBytes)
{
    unsigned char half = static_cast<unsigned char>(opCode);
    codeStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(opCode >> 8);
    codeStreams[currentSection] << std::hex << half;
    sectionCounter += 2;

    if (hasExtraBytes) {
        half = static_cast<unsigned char>(value);
        codeStreams[currentSection] << std::hex << half;
        half = static_cast<unsigned char>(value >> 8);
        codeStreams[currentSection] << std::hex << half;
        sectionCounter += 2;
    }
}

void CodeGenerator::changeSection(std::string section)
{
    currentSection++;
    numberOfSections++;
    sections[currentSection] = section;
    sectionCounter = 0;
}

void CodeGenerator::generateByte(char byteToGenerate)
{
    codeStreams[currentSection] << std::hex << byteToGenerate;
    sectionCounter += 1;
}

void CodeGenerator::generateWord(int16_t wordToGenerate)
{
    char half = static_cast<char>(wordToGenerate);
    codeStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(wordToGenerate >> 8);
    codeStreams[currentSection] << std::hex << half;

    sectionCounter += 2;
}

void CodeGenerator::generateLong(int32_t longToGenerate)
{
    char half = static_cast<char>(longToGenerate);
    codeStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(longToGenerate >> 8);
    codeStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(longToGenerate >> 16);
    codeStreams[currentSection] << std::hex << half;
    half = static_cast<unsigned char>(longToGenerate >> 24);
    codeStreams[currentSection] << std::hex << half;
    sectionCounter += 4;
}
