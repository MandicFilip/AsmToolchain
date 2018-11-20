//
// Created by mandula on 19.8.18..
//

#include "Linker.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>

void Linker::linkFiles(std::string *fileNames, int fileNum, ProgramInput* programInput) {
    this->fileNames = fileNames;
    this->fileNumber = fileNum;
    this->programInput = programInput;

    globalSymbolManager.restartManager();
    sectionManager.restartManager();

    handleFirstPass();
    doBetweenPasses();
    handleSecondPass();

    this->fileNames = NULL;
}

void Linker::handleFirstPass() {
    for (int i = 0; i < fileNumber; ++i) {
        FileInfo fileInfo;
        objFileReader.firstPassRead(const_cast<char *>(fileNames[i].data()), &fileInfo);
        addGlobalSymbols(&fileInfo);
        addSections(&fileInfo);
    }
}

void Linker::doBetweenPasses() {
    sectionManager.areSectionsOverlap();
    globalSymbolManager.checkIfNoneMissing();
    globalSymbolManager.getStartAddress();
}

void Linker::handleSecondPass() {
    for (int i = 0; i < fileNumber; ++i) {
        FileInfo fileInfo;
        objFileReader.secondPassRead(const_cast<char *>(fileNames[i].data()), &fileInfo);
        codeGenerator.fixFileCode(&fileInfo, &globalSymbolManager);

        fillProgramInfo(&fileInfo);

        //debagPrint(fileInfo);
        //print(fileInfo);
    }

    programInput->startAddress = globalSymbolManager.getStartAddress();
}

void Linker::addGlobalSymbols(FileInfo *fileInfo)
{
    for (std::vector<SymbolInfo>::iterator iter = fileInfo->symbols.begin();
            iter != fileInfo->symbols.end() ; ++iter) {
        if (iter->global && iter->defined) globalSymbolManager.insertFoundSymbol(iter->symbol, iter->value);
        if (iter->global && !iter->defined) globalSymbolManager.insertRequestedSymbol(iter->symbol, iter->value);
    }
}

void Linker::addSections(FileInfo *fileInfo)
{
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        sectionManager.addSection(fileInfo->sections[i]);
    }
}

void Linker::debagPrint(FileInfo &fileInfo)
{
    std::cout << std::hex << fileInfo.startPosition << " ";
    std::cout << std::hex << fileInfo.sectionsNumber << " ";
    std::cout << std::hex << fileInfo.symbols.size() << std::endl;

    std::string str[4];
    for (int i = 0; i < fileInfo.sectionsNumber; ++i) {
        for (std::vector<unsigned char>::iterator iter = fileInfo.codeBuffer[i].begin();
             iter != fileInfo.codeBuffer[i].end(); ++iter) {
            unsigned char c = *iter;
            str[i] += c;
        }
    }

    for (int i = 0; i < fileInfo.sectionsNumber; ++i) {
        std::cout << fileInfo.sections[i].section << " ";
        std::cout << std::hex << fileInfo.sections[i].startAddress << " ";
        std::cout << std::hex << fileInfo.sections[i].size << " ";
        std::cout << std::hex << fileInfo.sections[i].descriptor << std::endl;
    }

    for (int i = 0; i < fileInfo.sectionsNumber; ++i) {

        if (!strcmp(fileInfo.sections[i].section.data(), ".bss")) continue;

        int j = 0;
        std::cout << fileInfo.sections[i].section << std::endl;
        while (str[i].length() > 0) {
            unsigned char position = static_cast<unsigned char>(str[i][0]);
            str[i].erase(0, 1);
            std::cout << std::hex << std::setw(2) << std::setfill('0') << unsigned(position);
            std::cout << " ";

            j++;
            if (j == 12) {
                j = 0;
                std::cout << std::endl;
            }

        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void Linker::print(FileInfo info)
{
    globalSymbolManager.debagPrint();
}

void Linker::fillProgramInfo(FileInfo *fileInfo)
{
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        programInput->sections.push_back(fileInfo->sections[i]);
    }
    for (int i = 0; i < fileInfo->sectionsNumber; ++i) {
        programInput->codeSections.push_back(fileInfo->codeBuffer[i]);
    }
}
