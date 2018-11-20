//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_FIXPOSITIONOUTSIDEOFSECTION_H
#define SS_EMULATOR_FIXPOSITIONOUTSIDEOFSECTION_H

#include "LinkerException.h"

class FixPositionOutsideOfSection : public LinkerException
{
public:
    FixPositionOutsideOfSection()
    {
        setMessage(const_cast<char *>("Linker is accessing outside of section!"));
    }

};


#endif //SS_EMULATOR_FIXPOSITIONOUTSIDEOFSECTION_H
