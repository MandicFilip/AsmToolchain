//
// Created by mandula on 10.8.18..
//

#ifndef SS_PROJECT_NEGATIVEALIGNMENTEXCEPTION_H
#define SS_PROJECT_NEGATIVEALIGNMENTEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class NegativeAlignmentException : public AsmException
{
public:
    NegativeAlignmentException()
    {
        setMessage(const_cast<char*>("Error! Negative value has been sent to align directive!"));
    }

};


#endif //SS_PROJECT_NEGATIVEALIGNMENTEXCEPTION_H
