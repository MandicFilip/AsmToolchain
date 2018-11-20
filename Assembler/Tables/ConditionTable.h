//
// Created by mandula on 11.8.18..
//

#ifndef SS_PROJECT_CONDITIONTABLE_H
#define SS_PROJECT_CONDITIONTABLE_H


#include <string>
#include "../CommonTypes/CommonTypeWrappers.h"

class ConditionTable
{

    const static int CONDITION_TABLE_SIZE = 4;
    std::string conditionDictionary[CONDITION_TABLE_SIZE];

public:
    ConditionTable();

    uint16_t getConditionCode(std::string symbol);
};


#endif //SS_PROJECT_CONDITIONTABLE_H
