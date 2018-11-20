//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_SYMBOLNOTEXISTS_H
#define SS_EMULATOR_SYMBOLNOTEXISTS_H


#include "LinkerException.h"
#include <string>

class SymbolNotExists : public LinkerException
{
public:
    SymbolNotExists(uint16_t symbolId)
    {
        std::string message = "Symbol searched with id ";
        message.append(std::to_string(symbolId));
        message.append(" can't be found in table!");
        setMessage(const_cast<char*>(message.data()));
    }

    SymbolNotExists(std::string symbol)
    {
        std::string message = "Symbol ";
        message.append(symbol);
        message.append(" can't be found in table!");
        setMessage(const_cast<char*>(message.data()));
    }

};


#endif //SS_EMULATOR_SYMBOLNOTEXISTS_H
