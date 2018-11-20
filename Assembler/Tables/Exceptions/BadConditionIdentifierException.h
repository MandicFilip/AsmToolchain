//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_BADCONDITIONIDENTIFIEREXCEPTION_H
#define SS_PROJECT_BADCONDITIONIDENTIFIEREXCEPTION_H


#include "TableException.h"

class BadConditionIdentifierException : public TableException
{
public:
    BadConditionIdentifierException()
    {
        setMessage(const_cast<char*>("Error! Condition at the end of the operation code is not recognized!"));
    }

};


#endif //SS_PROJECT_BADCONDITIONIDENTIFIEREXCEPTION_H
