//
// Created by mandula on 23.8.18..
//

#ifndef SS_EMULATOR_BADOPERATIONCODEERROR_H
#define SS_EMULATOR_BADOPERATIONCODEERROR_H


#include "../../commonTypes.h"
#include <string>

class BadOperationCodeError : public MyException
{
public:
    BadOperationCodeError(char symbol)
    {
        std::string message = "Operation code ";
        message.append(&symbol);
        message.append(" is not valid! Execution stopped!");
        setMessage(const_cast<char*>(message.data()));
    }

};


#endif //SS_EMULATOR_BADOPERATIONCODEERROR_H
