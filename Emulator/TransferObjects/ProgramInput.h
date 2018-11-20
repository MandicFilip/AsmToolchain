//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_PROGRAMINPUT_H
#define SS_EMULATOR_PROGRAMINPUT_H


#include <vector>
#include "../commonTypes.h"
#include "../Linker/LinkerStructs.h"

struct ProgramInput
{
    uint16_t startAddress;
    std::vector<SectionInfo> sections;
    std::vector<std::vector<unsigned char>> codeSections;
};


#endif //SS_EMULATOR_PROGRAMINPUT_H
