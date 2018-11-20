//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_BADOPERATIONCODEEXCEPTION_H
#define SS_PROJECT_BADOPERATIONCODEEXCEPTION_H


#include "TableException.h"

class BadOperationCodeException : public TableException
{
public:
    BadOperationCodeException()
    {
        setMessage(const_cast<char*>("Error! Operation code is not recognized!"));
    }

};


#endif //SS_PROJECT_BADOPERATIONCODEEXCEPTION_H
