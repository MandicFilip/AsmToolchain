//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_NONESECTIONEXCEPTION_H
#define SS_PROJECT_NONESECTIONEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"
#include "TableException.h"

class NoneSectionException : public TableException
{
public:
    NoneSectionException()
    {
        setMessage(const_cast<char*>("Error! Code or data are not part of any section!"));
    }

};


#endif //SS_PROJECT_NONESECTIONEXCEPTION_H
