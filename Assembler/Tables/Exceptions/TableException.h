//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_TABLEEXCEPTION_H
#define SS_PROJECT_TABLEEXCEPTION_H


#include "../../CommonTypes/CommonTypeWrappers.h"

class TableException : public AssemblerException
{
public:
    TableException()
    {}

    TableException(const char* message) : AssemblerException(message)
    {}
};


#endif //SS_PROJECT_TABLEEXCEPTION_H
