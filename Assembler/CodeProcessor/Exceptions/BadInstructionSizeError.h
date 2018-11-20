//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_BADINSTRUCTIONSIZEERROR_H
#define SS_PROJECT_BADINSTRUCTIONSIZEERROR_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class BadInstructionSizeError : public AsmException
{
public:
    BadInstructionSizeError()
    {
        setMessage(const_cast<char*>("Error! Instruction has two operands in memory!"));
    }

};


#endif //SS_PROJECT_BADINSTRUCTIONSIZEERROR_H
