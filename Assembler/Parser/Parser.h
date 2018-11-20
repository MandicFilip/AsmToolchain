//
// Created by mandula on 25.7.18..
//

#ifndef SS_PROJECT_PARSER_H
#define SS_PROJECT_PARSER_H

#include <fstream>
#include <iostream>
#include "../TransferObjects/LineElements.h"
#include "LineDecoder.h"


class Parser
{
protected:
    std::fstream fileInput;
    LineDecoder lineDecoder;

    std::string readLine();
public:
    Parser(char* filePath);
    Parser();

    void reopenFile(char* filePath);

    virtual ~Parser();

    void parseLine(LineElements* lineElements);
};


#endif //SS_PROJECT_PARSER_H
