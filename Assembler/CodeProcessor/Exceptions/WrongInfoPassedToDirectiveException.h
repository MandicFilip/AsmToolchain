//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_WRONGINFOPASSEDTODIRECTIVE_H
#define SS_PROJECT_WRONGINFOPASSEDTODIRECTIVE_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class WrongInfoPassedToDirectiveException : public AsmException
{
public:
    WrongInfoPassedToDirectiveException()
    {
        setMessage(const_cast<char*>("Error! Wrong argument is passed to directive!"));
    }

};


#endif //SS_PROJECT_WRONGINFOPASSEDTODIRECTIVE_H
