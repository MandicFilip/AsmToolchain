//
// Created by mandula on 3.8.18..
//

#ifndef SS_PROJECT_MNEMONICTABLE_H
#define SS_PROJECT_MNEMONICTABLE_H


#include <string>
#include "../CodeProcessor/Handlers/OperandHandler.h"
#include "../CodeProcessor/Handlers/ZeroOperandHandler.h"
#include "../CodeProcessor/Handlers/OneOperandHandler.h"
#include "../CodeProcessor/Handlers/TwoOperandsHandler.h"

class MnemonicTable
{
    const static int MNEMONIC_TABLE_SIZE = 18;

    std::string mnemonicDictionary[MNEMONIC_TABLE_SIZE];
    OperandHandler* operandHandlers[MNEMONIC_TABLE_SIZE];
public:
    MnemonicTable(ZeroOperandHandler* zeroHandler, OneOperandHandler* oneHandler, TwoOperandsHandler* twoHandler);

    uint16_t getMnemonicCode(std::string symbol);
    OperandHandler* getOperandHandler(std::string symbol);
};


#endif //SS_PROJECT_MNEMONICTABLE_H
