//
// Created by mandula on 18.8.18..
//

#ifndef SS_EMULATOR_OBJFILEREADER_H
#define SS_EMULATOR_OBJFILEREADER_H


#include "../commonTypes.h"
#include "LinkerStructs.h"
#include <string>
#include <vector>


class ObjFileReader
{
public:

    void readObjFile(char* fileName, FileInfo* fileInfo);

    void firstPassRead(char* fileName, FileInfo* fileInfo);
    void secondPassRead(char* fileName, FileInfo* fileInfo);

private:
    FileInfo* fileInfo;

    void readBasicInfo(std::ifstream& in);
    void readSectionsInfo(std::ifstream& in);
    void readSymbols(std::ifstream& in);
    void readReallocationSection(std::ifstream& in);
    void readCodeSection(std::ifstream& in);
};


#endif //SS_EMULATOR_OBJFILEREADER_H
