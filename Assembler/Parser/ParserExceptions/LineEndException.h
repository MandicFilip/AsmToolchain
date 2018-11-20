//
// Created by mandula on 28.7.18..
//

#ifndef SS_PROJECT_LINEENDEXCEPTION_H
#define SS_PROJECT_LINEENDEXCEPTION_H

#include "../../CommonTypes/CommonTypeWrappers.h"

class LineEndException : public AssemblerException
{
public:
    const char* what() const noexcept override { return "Line end!"; }
};


#endif //SS_PROJECT_LINEENDEXCEPTION_H
