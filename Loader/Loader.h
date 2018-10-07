//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_LOADER_H
#define SS_EMULATOR_LOADER_H


#include "../TransferObjects/ProgramInput.h"
#include "../System/System.h"

class Loader
{
    void checkIORegistersOverlap(ProgramInput& programInput);

public:
    void loadProgram(ProgramInput& programInput, System* system);
};


#endif //SS_EMULATOR_LOADER_H
