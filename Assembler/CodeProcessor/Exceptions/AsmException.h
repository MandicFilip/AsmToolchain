//
// Created by mandula on 12.8.18..
//

#ifndef SS_PROJECT_ASSEMBLYEXCEPTION_H
#define SS_PROJECT_ASSEMBLYEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"

class AsmException : public AssemblerException
{
public:
    AsmException()
    {}

    AsmException(const char* message) : AssemblerException(message)
    {}
};


#endif //SS_PROJECT_ASSEMBLYEXCEPTION_H
