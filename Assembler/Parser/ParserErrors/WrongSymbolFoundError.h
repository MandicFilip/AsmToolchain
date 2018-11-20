//
// Created by mandula on 30.7.18..
//

#ifndef SS_PROJECT_BADLABELPLACEERROR_H
#define SS_PROJECT_BADLABELPLACEERROR_H

#include "ParserError.h"

class WrongSymbolFoundError : public ParserError
{
public:
    WrongSymbolFoundError(char* message)
    {
        setMessage(message);
    }

};

#endif //SS_PROJECT_BADLABELPLACEERROR_H
