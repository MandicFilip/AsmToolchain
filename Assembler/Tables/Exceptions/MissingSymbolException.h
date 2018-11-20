//
// Created by mandula on 8.8.18..
//

#ifndef SS_PROJECT_MISSINGSYMBOLEXCEPTION_H
#define SS_PROJECT_MISSINGSYMBOLEXCEPTION_H

#include "TableException.h"

class MissingSymbolException : public TableException
{
public:
    MissingSymbolException()
    {
        setMessage(const_cast<char*>("Error! Symbol which is searched does not exists in table!"));
    }

};


#endif //SS_PROJECT_MISSINGSYMBOLEXCEPTION_H
