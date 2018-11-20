//
// Created by mandula on 12.8.18..
//

#ifndef SS_PROJECT_FAILTOCREATEOBJFILEEXCEPTION_H
#define SS_PROJECT_FAILTOCREATEOBJFILEEXCEPTION_H


#include "AsmException.h"

class FailToCreateObjFileException : public AsmException
{

public:
    FailToCreateObjFileException()
    {
        setMessage(const_cast<char*>("Error! Failed to open output obj file!"));
    }

};


#endif //SS_PROJECT_FAILTOCREATEOBJFILEEXCEPTION_H
