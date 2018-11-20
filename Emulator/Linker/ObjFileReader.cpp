//
// Created by mandula on 18.8.18..
//

#include "ObjFileReader.h"
#include <iostream>
#include <fstream>

void ObjFileReader::readObjFile(char* fileName, FileInfo* fileInfo)
{
    std::ifstream in(fileName, std::ios::binary);

    if (!in.is_open())
        return;

    this->fileInfo = fileInfo;

    readBasicInfo(in);
    readSectionsInfo(in);
    readSymbols(in);
    readReallocationSection(in);
    readCodeSection(in);

    in.close();
}

void ObjFileReader::readBasicInfo(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&fileInfo->startPosition), sizeof(uint16_t));
    in.read(reinterpret_cast<char*>(&fileInfo->sectionsNumber), sizeof(uint16_t));
    in.read(reinterpret_cast<char*>(&fileInfo->symbolsNumber), sizeof(uint16_t));
}

void ObjFileReader::readSectionsInfo(std::ifstream& in)
{
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        uint16_t readSize;
        in.read(reinterpret_cast<char*>(&readSize), sizeof(uint16_t));
        fileInfo->sections[i].section.resize(readSize);
        in.read(const_cast<char*>(fileInfo->sections[i].section.data()), readSize);
        in.read(reinterpret_cast<char*>(&fileInfo->sections[i].startAddress), sizeof(uint16_t));
        in.read(reinterpret_cast<char*>(&fileInfo->sections[i].size), sizeof(uint16_t));
        in.read(reinterpret_cast<char*>(&fileInfo->sections[i].descriptor), sizeof(uint16_t));
    }
}

void ObjFileReader::readSymbols(std::ifstream& in)
{
    for (int i = 0; i < fileInfo->symbolsNumber - 1; ++i) { //-1 for UND which is not in file
        SymbolInfo tmp;
        uint16_t readSize;
        in.read(reinterpret_cast<char*>(&readSize), sizeof(uint16_t));
        tmp.symbol.resize(readSize);
        in.read(const_cast<char*>(tmp.symbol.data()), readSize);
        in.read(reinterpret_cast<char*>(&tmp.symbolId), sizeof(uint16_t));
        in.read(reinterpret_cast<char*>(&tmp.global), sizeof(uint16_t));
        in.read(reinterpret_cast<char*>(&tmp.value), sizeof(uint16_t));
        in.read(reinterpret_cast<char*>(&tmp.defined), sizeof(uint16_t));

        in.read(reinterpret_cast<char*>(&readSize), sizeof(uint16_t));
        tmp.section.resize(readSize);
        in.read(const_cast<char*>(tmp.section.data()), readSize);
        in.read(reinterpret_cast<char*>(&tmp.offset), sizeof(uint16_t));
        fileInfo->symbols.push_back(tmp);
    }
}

void ObjFileReader::readReallocationSection(std::ifstream& in)
{
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        if (!strcmp(fileInfo->sections[i].section.data(), ".bss")) continue;

        uint16_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(uint16_t));
        for (int j = 0; j < size; ++j) {
            ReallocationInfo tmp;
            in.read(reinterpret_cast<char*>(&tmp.place), sizeof(uint16_t));
            in.read(reinterpret_cast<char*>(&tmp.reallocationType), sizeof(uint16_t));
            in.read(reinterpret_cast<char*>(&tmp.symbolToBound), sizeof(uint16_t));
            fileInfo->reallocationRecordSections[i].push_back(tmp);
        }
    }
}

void ObjFileReader::readCodeSection(std::ifstream& in)
{
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        if (!strcmp(fileInfo->sections[i].section.data(), ".bss")) continue;

        uint16_t size = fileInfo->sections[i].size;
        for (int j = 0; j < size; ++j) {
            unsigned char data;
            in.read(reinterpret_cast<char*>(&data), sizeof(unsigned char));
            fileInfo->codeBuffer[i].push_back(data);
        }
    }
}

void ObjFileReader::firstPassRead(char *fileName, FileInfo* fileInfo) {
    std::ifstream in(fileName, std::ios::binary);

    if (!in.is_open())
        return;

    this->fileInfo = fileInfo;

    readBasicInfo(in);
    readSectionsInfo(in);
    readSymbols(in);

    in.close();
}

void ObjFileReader::secondPassRead(char *fileName, FileInfo* fileInfo) {
    std::ifstream in(fileName, std::ios::binary);

    if (!in.is_open())
        return;

    this->fileInfo = fileInfo;

    readBasicInfo(in);
    readSectionsInfo(in);
    readSymbols(in);
    readReallocationSection(in);
    readCodeSection(in);

    in.close();
}
