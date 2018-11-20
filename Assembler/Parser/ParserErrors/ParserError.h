//
// Created by mandula on 30.7.18..
//

#ifndef SS_PROJECT_PARSERERROR_H
#define SS_PROJECT_PARSERERROR_H

#include <cstdlib>
#include <cstring>
#include "../../CommonTypes/CommonTypeWrappers.h"

class ParserError : public AssemblerException
{

public:
    ParserError() {}

    ParserError(const char* string) : AssemblerException(string)
    {

    }
};

#endif //SS_PROJECT_PARSERERROR_H
