//
// Created by mandula on 23.8.18..
//

#ifndef SS_EMULATOR_WRONGDSTOPERANDERROR_H
#define SS_EMULATOR_WRONGDSTOPERANDERROR_H

#include <string>
#include "../../commonTypes.h"

class WrongDstOperandError : public MyException
{
public:
    WrongDstOperandError()
    {
        setMessage(const_cast<char *>("Wrong address type is used for destination operand! Execution stopped!"));
    }

};


#endif //SS_EMULATOR_WRONGDSTOPERANDERROR_H
