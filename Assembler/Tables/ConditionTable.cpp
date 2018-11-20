//
// Created by mandula on 11.8.18..
//

#include "ConditionTable.h"
#include "Exceptions/BadConditionIdentifierException.h"

ConditionTable::ConditionTable()
{
    conditionDictionary[0] = "eq";
    conditionDictionary[1] = "ne";
    conditionDictionary[2] = "gt";
    conditionDictionary[3] = "al";
}

uint16_t ConditionTable::getConditionCode(std::string symbol)
{
    for (int i = 0; i < CONDITION_TABLE_SIZE; ++i) {
        if (!strcmp(symbol.data(), conditionDictionary[i].data())) return static_cast<uint16_t>(i);
    }
    throw BadConditionIdentifierException();
}
