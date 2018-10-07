//
// Created by mandula on 20.8.18..
//

#include <iostream>
#include "Loader.h"
#include "SegmentationFaultInLoader.h"

void Loader::loadProgram(ProgramInput& programInput, System *system)
{
    checkIORegistersOverlap(programInput);

    for (int i = 0; i < programInput.sections.size(); ++i) {
        System::SegmentInfo segment;
        segment.startAddress = programInput.sections[i].startAddress;
        segment.size = programInput.sections[i].size;
        segment.descriptor = programInput.sections[i].descriptor;
        system->segmentTable.push_back(segment);

        if (!strcmp(programInput.sections[i].section.data(), ".bss")) continue;

        uint16_t position = programInput.sections[i].startAddress;
        for (int j = 0; j < programInput.sections[i].size; ++j) {
            system->memory[position++] = programInput.codeSections[i][j]; //load code into memory
        }

    }

    system->registers[7] = programInput.startAddress;

    uint16_t beginRoutine = system->readWordFromMemory(0);
    if (beginRoutine != 0) {
        system->setInterrupt(system->INIT_ROUTINE);
    }
    system->writeInPSW(0x8000);
}

void Loader::checkIORegistersOverlap(ProgramInput &programInput)
{
    for (int i = 0; i < programInput.sections.size(); ++i) {
        if ((long)programInput.sections[i].startAddress + programInput.sections[i].size >= IO_SECTION_START)
            throw SegmentationFaultInLoader();
    }
}
