//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_LCOVERFLOWEXCEPTION_H
#define SS_PROJECT_LCOVERFLOWEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class LCOverflowException : public AsmException
{
public:
    LCOverflowException()
    {
        setMessage(const_cast<char*>("Error! Value sent to directive caused overflow on location counter!"));
    }

};


#endif //SS_PROJECT_LCOVERFLOWEXCEPTION_H
