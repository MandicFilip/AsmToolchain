//
// Created by mandula on 19.8.18..
//

#include <string>
#include "LinkerException.h"

#ifndef SS_EMULATOR_GLOBALSYMBOLALREADYFOUND_H
#define SS_EMULATOR_GLOBALSYMBOLALREADYFOUND_H


class GlobalSymbolAlreadyFound : public LinkerException
{

public:
    GlobalSymbolAlreadyFound(char* symbol)
    {
        std::string message = "Global Symbol ";
        message.append(symbol);
        message.append(" is defined multiple times!");
        setMessage(const_cast<char*>(message.data()));
    }

};

#endif //SS_EMULATOR_GLOBALSYMBOLALREADYFOUND_H
