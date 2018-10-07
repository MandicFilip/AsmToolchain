//
// Created by mandula on 23.8.18..
//

#ifndef SS_EMULATOR_BADCONDITIONERROR_H
#define SS_EMULATOR_BADCONDITIONERROR_H

#include <string>
#include "../../commonTypes.h"

class BadConditionError : public MyException
{
public:
    BadConditionError(char symbol)
    {
        std::string message = "Condition code ";
        message.append(&symbol);
        message.append(" is not valid! Execution stopped!");
        setMessage(const_cast<char*>(message.data()));
    }

};


#endif //SS_EMULATOR_BADCONDITIONERROR_H
