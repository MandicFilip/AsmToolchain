//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_STARTSYMBOLMISSING_H
#define SS_EMULATOR_STARTSYMBOLMISSING_H


#include "LinkerException.h"

class StartSymbolMissing : public LinkerException
{
public:
    StartSymbolMissing()
    {
        setMessage(const_cast<char *>("Start symbol is not defined!"));
    }

};


#endif //SS_EMULATOR_STARTSYMBOLMISSING_H
