//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_BADDSTOPERANDEXCEPTION_H
#define SS_PROJECT_BADDSTOPERANDEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class BadDstOperandException : public AsmException
{
public:
    BadDstOperandException()
    {
        setMessage(const_cast<char*>("Error! Illegal operand type is used at destination field!"));
    }

};


#endif //SS_PROJECT_BADDSTOPERANDEXCEPTION_H
