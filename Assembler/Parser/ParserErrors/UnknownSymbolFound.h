//
// Created by mandula on 29.7.18..
//

#ifndef SS_PROJECT_UNKNOWNSYMBOLFOUND_H
#define SS_PROJECT_UNKNOWNSYMBOLFOUND_H

#include "ParserError.h"

class UnknownSymbolFound : public ParserError
{
public:
    UnknownSymbolFound()
    {
        setMessage(const_cast<char*>("Syntax error! Unknown symbol is found."));
    }

};

#endif //SS_PROJECT_UNKNOWNSYMBOLFOUND_H
