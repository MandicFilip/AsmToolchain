//
// Created by mandula on 10.8.18..
//

#ifndef SS_PROJECT_ENDDIRECTIVEFOUNDEXCEPTION_H
#define SS_PROJECT_ENDDIRECTIVEFOUNDEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "AsmException.h"

class EndDirectiveFoundException : AssemblerException
{
public:
    EndDirectiveFoundException()
    {
        setMessage(const_cast<char*>("File has been read!"));
    }

};


#endif //SS_PROJECT_ENDDIRECTIVEFOUNDEXCEPTION_H
