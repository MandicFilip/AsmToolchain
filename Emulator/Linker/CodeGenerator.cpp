//
// Created by mandula on 19.8.18..
//

#include "CodeGenerator.h"
#include "Exceptions/SymbolNotExists.h"
#include "Exceptions/FixPositionOutsideOfSection.h"

uint16_t CodeGenerator::getWordFromCodeBuffer(uint16_t position, int bufferNum)
{
    if (position > fileInfo->codeBuffer[bufferNum].size() - 2) throw FixPositionOutsideOfSection();

    uint16_t ret = 0;
    ret = fileInfo->codeBuffer[bufferNum][position];
    uint16_t tmp = 0;
    tmp = fileInfo->codeBuffer[bufferNum][position + 1];
    tmp <<= 8;
    ret |= tmp;
    return ret;
}

void CodeGenerator::setWordInCodeBuffer(uint16_t word, uint16_t position, int bufferNum)
{
    if (position > fileInfo->codeBuffer[bufferNum].size() - 2) throw FixPositionOutsideOfSection();

    unsigned char lower = static_cast<unsigned char>(word);
    unsigned char higher = static_cast<unsigned char>(word >> 8);

    fileInfo->codeBuffer[bufferNum][position] = lower;
    fileInfo->codeBuffer[bufferNum][position + 1] = higher;
}

bool CodeGenerator::isSymbolGlobal(uint16_t symbolId)
{
    for (std::vector<SymbolInfo>::iterator iter = fileInfo->symbols.begin();
         iter != fileInfo->symbols.end(); ++iter) {
        if (symbolId == iter->symbolId) return iter->global;
    }
    throw SymbolNotExists(symbolId);
}

std::string CodeGenerator::getSymbolFromId(uint16_t symbolId)
{
    for (std::vector<SymbolInfo>::iterator iter = fileInfo->symbols.begin();
         iter != fileInfo->symbols.end(); ++iter) {
        if (symbolId == iter->symbolId) return iter->symbol;
    }
    throw SymbolNotExists(symbolId);
}

void CodeGenerator::fixFileCode(FileInfo *fileInfo, GlobalSymbolManager* globalSymbolManager)
{
    this->fileInfo = fileInfo;
    this->globalSymbolManager = globalSymbolManager;

    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        if (!strcmp(fileInfo->sections[i].section.data(), ".bss")) continue;

        std::vector<ReallocationInfo>::iterator reallocationIterator = fileInfo->reallocationRecordSections[i].begin();
        while (reallocationIterator != fileInfo->reallocationRecordSections[i].end()) {

            uint16_t symbolId = reallocationIterator->symbolToBound;
            if (reallocationIterator->reallocationType == apsolutely) {
                if (isSymbolGlobal(symbolId)) handleGlobalApsolute(*reallocationIterator, i);
                else handleSectionApsolute(*reallocationIterator, i);

            }
            else {
                if (isSymbolGlobal(symbolId)) handleGlobalRelative(*reallocationIterator, i, fileInfo->sections[i].startAddress);
                else handleSectionRelative(*reallocationIterator, i, fileInfo->sections[i].startAddress);
            }

            reallocationIterator++;
        }
    }

    this->globalSymbolManager = NULL;
    this->fileInfo = NULL;
}

void CodeGenerator::handleGlobalApsolute(ReallocationInfo &info, int bufferNum)
{
    std::string symbol = getSymbolFromId(info.symbolToBound);
    uint16_t symbolAddress = globalSymbolManager->getSymbolAddress(symbol);
    setWordInCodeBuffer(symbolAddress, info.place, bufferNum);
}

void CodeGenerator::handleSectionApsolute(ReallocationInfo &info, int bufferNum)
{
    uint16_t symbolAddress = findSymbolAddress(info.symbolToBound);
    symbolAddress += getWordFromCodeBuffer(info.place, bufferNum);
    setWordInCodeBuffer(symbolAddress, info.place, bufferNum);
}

void CodeGenerator::handleGlobalRelative(ReallocationInfo &info, int bufferNum, uint16_t sectionAddress)
{
    std::string symbol = getSymbolFromId(info.symbolToBound);

    int16_t symbolAddress = globalSymbolManager->getSymbolAddress(symbol);
    symbolAddress -= sectionAddress;
    symbolAddress -= info.place;
    symbolAddress += getWordFromCodeBuffer(info.place, bufferNum);

    setWordInCodeBuffer(static_cast<uint16_t>(symbolAddress), info.place, bufferNum);
}

void CodeGenerator::handleSectionRelative(ReallocationInfo &info, int bufferNum, uint16_t sectionAddress)
{
    int16_t symbolAddress = findSymbolAddress(info.symbolToBound);
    symbolAddress -= sectionAddress;
    symbolAddress -= info.place;
    symbolAddress += getWordFromCodeBuffer(info.place, bufferNum);

    setWordInCodeBuffer(static_cast<uint16_t>(symbolAddress), info.place, bufferNum);
}

uint16_t CodeGenerator::findSymbolAddress(uint16_t symbolId)
{
    for (std::vector<SymbolInfo>::iterator iter = fileInfo->symbols.begin();
            iter !=  fileInfo->symbols.end(); ++iter) {
        if (iter->symbolId == symbolId) return iter->value;
    }
    throw SymbolNotExists(symbolId);
}
