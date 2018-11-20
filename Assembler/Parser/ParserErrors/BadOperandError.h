//
// Created by mandula on 2.8.18..
//

#ifndef SS_PROJECT_BADOPERANDERROR_H
#define SS_PROJECT_BADOPERANDERROR_H


#include "ParserError.h"
#include "string"

class BadOperandError : public ParserError
{
public:
    BadOperandError(char* symbol)
    {
        std::string message = "Syntax error! Symbol ";
        message.append(symbol);
        message.append("is not recognized as operand.");
        setMessage(const_cast<char*>(message.data()));
    }

};


#endif //SS_PROJECT_BADOPERANDERROR_H
