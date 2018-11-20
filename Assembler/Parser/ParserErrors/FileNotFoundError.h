//
// Created by mandula on 29.7.18..
//

#ifndef SS_PROJECT_FILENOTFOUNDERROR_H
#define SS_PROJECT_FILENOTFOUNDERROR_H

#include <string>
#include "ParserError.h"

class FileNotFoundError : public ParserError
{
public:
    FileNotFoundError(char* fileName)
    {
        std::string message = "File ";
        message.append(fileName);
        message.append(" can't be opened or does not exist!");
        setMessage(const_cast<char*>(message.data()));
    }

};

#endif //SS_PROJECT_FILENOTFOUNDERROR_H
