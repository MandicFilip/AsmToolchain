//
// Created by mandula on 3.8.18..
//

#ifndef SS_PROJECT_TOOMANYOPERANDSERROR_H
#define SS_PROJECT_TOOMANYOPERANDSERROR_H

#include "ParserError.h"

class TooManyOperandsError : public ParserError
{
public:
    TooManyOperandsError()
    {
        setMessage(const_cast<char*>("Line has too many operands!"));
    }

};

#endif //SS_PROJECT_TOOMANYOPERANDSERROR_H
