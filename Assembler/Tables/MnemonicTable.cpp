//
// Created by mandula on 3.8.18..
//

#include <cstring>
#include <algorithm>
#include "MnemonicTable.h"
#include "Exceptions/BadOperationCodeException.h"
#include "../CodeProcessor/ZeroOperandHandler.h"

MnemonicTable::MnemonicTable(ZeroOperandHandler* zeroHandler, OneOperandHandler* oneHandler, TwoOperandsHandler* twoHandler)
{
    zeroHandler->setMnemonicTable(this);
    oneHandler->setMnemonicTable(this);
    twoHandler->setMnemonicTable(this);

    mnemonicDictionary[0] = "add";
    mnemonicDictionary[1] = "sub";
    mnemonicDictionary[2] = "mul";
    mnemonicDictionary[3] = "div";
    mnemonicDictionary[4] = "cmp";
    mnemonicDictionary[5] = "and";
    mnemonicDictionary[6] = "or";
    mnemonicDictionary[7] = "not";
    mnemonicDictionary[8] = "test";
    mnemonicDictionary[9] = "push";
    mnemonicDictionary[10] = "pop";
    mnemonicDictionary[11] = "call";
    mnemonicDictionary[12] = "iret";
    mnemonicDictionary[13] = "mov";
    mnemonicDictionary[14] = "shl";
    mnemonicDictionary[15] = "shr";
    mnemonicDictionary[16] = "ret";
    mnemonicDictionary[17] = "jmp";

    operandHandlers[0] = twoHandler;
    operandHandlers[1] = twoHandler;
    operandHandlers[2] = twoHandler;
    operandHandlers[3] = twoHandler;
    operandHandlers[4] = twoHandler;
    operandHandlers[5] = twoHandler;
    operandHandlers[6] = twoHandler;
    operandHandlers[7] = twoHandler;
    operandHandlers[8] = twoHandler;
    operandHandlers[9] = oneHandler;
    operandHandlers[10] = oneHandler;
    operandHandlers[11] = oneHandler;
    operandHandlers[12] = zeroHandler;
    operandHandlers[13] = twoHandler;
    operandHandlers[14] = twoHandler;
    operandHandlers[15] = twoHandler;
    operandHandlers[16] = zeroHandler;
    operandHandlers[17] = oneHandler;

}

uint16_t MnemonicTable::getMnemonicCode(std::string symbol)
{
    std::transform(symbol.begin(), symbol.end(), symbol.begin(), ::tolower);
    for (int i = 0; i < MNEMONIC_TABLE_SIZE; ++i) {
        if (!strcmp(symbol.data(), mnemonicDictionary[i].data())) return i;
    }
    throw BadOperationCodeException();
}

OperandHandler* MnemonicTable::getOperandHandler(std::string symbol)
{
    std::transform(symbol.begin(), symbol.end(), symbol.begin(), ::tolower);
    uint16_t index = getMnemonicCode(symbol);
    return operandHandlers[index];
}
