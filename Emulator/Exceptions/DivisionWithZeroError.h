//
// Created by mandula on 26.8.18..
//

#ifndef SS_EMULATOR_DIVISIONWITHZEROERROR_H
#define SS_EMULATOR_DIVISIONWITHZEROERROR_H


#include "../../commonTypes.h"
#include <string>

class DivisionWithZeroError : public MyException
{
public:
    DivisionWithZeroError()
    {
        std::string message = "Second operand in div operation was 0";
        setMessage(const_cast<char*>(message.data()));
    }

};


#endif //SS_EMULATOR_DIVISIONWITHZEROERROR_H
