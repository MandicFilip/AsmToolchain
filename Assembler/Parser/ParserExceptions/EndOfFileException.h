//
// Created by mandula on 25.7.18..
//

#ifndef SS_PROJECT_ENDOFFILEEXCEPTION_H
#define SS_PROJECT_ENDOFFILEEXCEPTION_H

#include <exception>
#include "../../CommonTypes/CommonTypeWrappers.h"

class EndOfFileException : public AssemblerException
{

public:
    const char* what() const noexcept override { return "File has been read correctly until the end";}
};


#endif //SS_PROJECT_ENDOFFILEEXCEPTION_H
