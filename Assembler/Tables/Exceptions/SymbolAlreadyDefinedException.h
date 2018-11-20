//
// Created by mandula on 8.8.18..
//

#ifndef SS_PROJECT_SYMBOLALREADYDEFINEDEXCEPTION_H
#define SS_PROJECT_SYMBOLALREADYDEFINEDEXCEPTION_H

#include "TableException.h"

class SymbolAlreadyDefinedException : public TableException
{
public:
    SymbolAlreadyDefinedException()
    {
        setMessage(const_cast<char*>("Error! Duplicate symbol definition in file!"));
    }

};


#endif //SS_PROJECT_SYMBOLALREADYDEFINEDEXCEPTION_H
