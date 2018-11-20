//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_SECTIONALREADYDEFINED_H
#define SS_PROJECT_SECTIONALREADYDEFINED_H

#include "TableException.h"


class SectionAlreadyDefinedException : public TableException
{
public:
    SectionAlreadyDefinedException()
    {
        setMessage(const_cast<char*>("Error! Duplicate section name in file!"));
    }

};


#endif //SS_PROJECT_SECTIONALREADYDEFINED_H
