//
// Created by mandula on 3.8.18..
//

#ifndef SS_PROJECT_MNEMONICTABLE_H
#define SS_PROJECT_MNEMONICTABLE_H


#include <string>
#include "../CodeProcessor/OperandHandler.h"
#include "../CodeProcessor/ZeroOperandHandler.h"
#include "../CodeProcessor/OneOperandHandler.h"
#include "../CodeProcessor/TwoOperandsHandler.h"

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
