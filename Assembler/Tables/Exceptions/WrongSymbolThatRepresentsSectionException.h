//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_WRONGSYMBOLTHATREPRESENTSSECTIONEXCEPTION_H
#define SS_PROJECT_WRONGSYMBOLTHATREPRESENTSSECTIONEXCEPTION_H

#include "TableException.h"

class WrongSymbolThatRepresentsSectionException : public TableException
{
public:
    WrongSymbolThatRepresentsSectionException()
    {
        setMessage(const_cast<char*>("Error! Symbol is not recognized as section name!"));
    }

};


#endif //SS_PROJECT_WRONGSYMBOLTHATREPRESENTSSECTIONEXCEPTION_H
