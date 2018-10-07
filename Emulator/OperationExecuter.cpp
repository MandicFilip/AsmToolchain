//
// Created by mandula on 22.8.18..
//

#include "OperationExecuter.h"
#include "Exceptions/BadOperationCodeError.h"
#include "Exceptions/BadConditionError.h"
#include "Exceptions/WrongDstOperandError.h"
#include "Exceptions/DivisionWithZeroError.h"

const uint16_t ZERO_BIT_MASK = 1;
const uint16_t OVERFLOW_BIT_MASK = 2;
const uint16_t NEGATIVE_BIT_MASK = 8;

OperationExecuter::OperationExecuter(System *system) : system(system)
{}

void OperationExecuter::executeInstruction(InstructionInfo *info)
{
    if (!checkCondition(info)) return;

    if (info->opCode > (unsigned char)SHR) throw BadOperationCodeError(info->opCode);

    OperationCodes code = static_cast<OperationCodes>(info->opCode);

    switch (code) {
        case ADD:
            doAdd(info);
            break;
        case SUB:
            doSub(info);
            break;
        case MUL:
            doMul(info);
            break;
        case DIV:
            doDiv(info);
            break;
        case CMP:
            doCmp(info);
            break;
        case AND:
            doAnd(info);
            break;
        case OR:
            doOr(info);
            break;
        case NOT:
            doNot(info);
            break;
        case TEST:
            doTest(info);
            break;
        case PUSH:
            doPush(info);
            break;
        case POP:
            doPop(info);
            break;
        case CALL:
            doCall(info);
            break;
        case IRET:
            doIret(info);
            break;
        case MOV:
            doMov(info);
            break;
        case SHL:
            doShl(info);
            break;
        case SHR:
            doShr(info);
            break;
    }
}

bool OperationExecuter::checkCondition(InstructionInfo *info)
{
    uint16_t pswState = system->readPSW();

    if (info->condition > (unsigned char)ALWAYS) throw BadConditionError(info->condition);

    Conditions condition = static_cast<Conditions>(info->condition);
    bool result = false;
    switch (condition) {
        case EQUAL:
            if (pswState & ZERO_BIT_MASK) result = true;
            break;
        case NOT_EQUAL:
            if (!(pswState & ZERO_BIT_MASK)) result = true;
            break;
        case GREATER_THEN:
            if (!(((pswState & OVERFLOW_BIT_MASK) ^ (pswState & NEGATIVE_BIT_MASK)) ||
                (pswState & ZERO_BIT_MASK))) result = true;
            break;
        case ALWAYS: result = true;
    }
    return result;
}

void OperationExecuter::doAdd(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp + secondOp;

    setAllPswFlags(result, firstOp, secondOp, info->opCode);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doSub(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp - secondOp;

    setAllPswFlags(result, firstOp, secondOp, info->opCode);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doMul(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp * secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doDiv(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    if (secondOp == 0) throw DivisionWithZeroError();

    int16_t result = firstOp / secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doCmp(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp - secondOp;

    setAllPswFlags(result, firstOp, secondOp, info->opCode);
}

void OperationExecuter::doAnd(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp & secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doOr(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp | secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doNot(InstructionInfo *info)
{
    int16_t secondOp = getSrcValue(info);

    int16_t result = !secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doTest(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp & secondOp;

    setZeroNegativeFlags(result);
}

void OperationExecuter::doPush(InstructionInfo *info)
{
    int16_t operand = getSrcValue(info);
    system->pushWordToStack(operand);
}

void OperationExecuter::doPop(InstructionInfo *info)
{
    int16_t tmp = system->popWordFromStack();
    writeResultIntoDst(info, tmp);
}

void OperationExecuter::doCall(InstructionInfo *info)
{
    int16_t operand = getSrcValue(info);

    int16_t tmp = system->readPC();
    system->pushWordToStack(tmp);

    system->writeInPC(operand);
}

void OperationExecuter::doIret(InstructionInfo *info)
{
    int16_t tmp = system->popWordFromStack();
    system->writeInPSW(tmp);

    tmp = system->popWordFromStack();
    system->writeInPC(tmp);
}

void OperationExecuter::doMov(InstructionInfo *info)
{
    int16_t secondOp = getSrcValue(info);

    int16_t result = secondOp;

    setZeroNegativeFlags(result);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doShl(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp << secondOp;

    setZeroNegativeCarryFlags(result, firstOp, secondOp, info->opCode);
    writeResultIntoDst(info, result);
}

void OperationExecuter::doShr(InstructionInfo *info)
{
    int16_t firstOp = getDstValue(info);
    int16_t secondOp = getSrcValue(info);

    int16_t result = firstOp >> secondOp;

    setZeroNegativeCarryFlags(result, firstOp, secondOp, info->opCode);
    writeResultIntoDst(info, result);
}

void OperationExecuter::setAllPswFlags(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode)
{
    uint16_t pswState = system->readPSW();
    pswState >>= 4;
    pswState <<= 4;
    if (isZero(result)) pswState +=1;
    if (isOverflow(result, firstOp, secondOp, opCode)) pswState += 2;
    if (isCarry(result, firstOp, secondOp, opCode)) pswState += 4;
    if (isNegative(result)) pswState += 8;
    system->writeInPSW(pswState);
}

void OperationExecuter::setZeroNegativeFlags(int16_t result)
{
    uint16_t pswState = system->readPSW();
    pswState >>= 4;
    pswState <<= 4;
    if (isZero(result)) pswState +=1;
    if (isNegative(result)) pswState += 8;
    system->writeInPSW(pswState);
}

void OperationExecuter::setZeroNegativeCarryFlags(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode)
{
    uint16_t pswState = system->readPSW();
    pswState >>= 4;
    pswState <<= 4;
    if (isZero(result)) pswState +=1;
    if (isCarry(result, firstOp, secondOp, opCode)) pswState += 4;
    if (isNegative(result)) pswState += 8;
    system->writeInPSW(pswState);
}

bool OperationExecuter::isZero(int16_t result)
{
    return static_cast<bool>(!result);
}

bool OperationExecuter::isOverflow(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode)
{
    if (opCode == ADD) {
        if ((firstOp < 0) && (secondOp < 0) && (result >= 0)) return true;
        if ((firstOp > 0) && (secondOp > 0) && (result <= 0)) return true;
    }
    else if (opCode == SUB || opCode == CMP) {
        secondOp *= -1;
        if ((firstOp < 0) && (secondOp < 0) && (result >= 0)) return true;
        if ((firstOp > 0) && (secondOp > 0) && (result <= 0)) return true;
    }
    return false;
}

bool OperationExecuter::isCarry(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode)
{
    if (opCode == ADD) {
        uint16_t highestBitMask = 1;
        highestBitMask <<= 15;
        if ((firstOp & highestBitMask) && (secondOp & highestBitMask)) return true;
        if (!(firstOp & highestBitMask) && !(secondOp & highestBitMask)) return false;
        return !(result & highestBitMask);
    }
    else if (opCode == SUB || opCode == CMP) {
        int carry = 0;
        for (int i = 0; i < 16; ++i) { //16 bits
            if ((((firstOp >> i) & 1) - ((secondOp >> i) & 1) - carry) < 0) carry = 1;
            else carry = 0;
        }
        return carry == 1;
    }
    else if (opCode == SHL) {
        if (secondOp == 0 || secondOp > 16) return false;
        uint16_t mask = 1;
        mask <<= 15;
        for (int i = 0; i < secondOp - 1; ++i) {
            mask >>= 1;
        }
        return (firstOp & mask) != 0;

    }
    else if (opCode == SHR) {
        if (secondOp == 0 || secondOp > 16) return false;
        uint16_t mask = 1;
        for (int i = 0; i < secondOp - 1; ++i) {
            mask <<= 1;
        }
        return (firstOp & mask) != 0;
    }

    return false;
}

bool OperationExecuter::isNegative(int16_t result)
{
    return result < 0;
}

int16_t OperationExecuter::getDstValue(InstructionInfo *info)
{
    if (info->dstCode == 0) throw WrongDstOperandError();

    if (info->dstCode == 1) return system->readRegister(info->dstReg);
    return info->operandPlace;
}

int16_t OperationExecuter::getSrcValue(InstructionInfo *info)
{
    if (info->srcCode == 0 && info->srcReg == 7) return system->readPSW();
    if (info->srcCode == 0) return info->extraWord;
    if (info->srcCode == 1) return system->readRegister(info->srcReg);
    return info->operandPlace;
}

void OperationExecuter::writeResultIntoDst(InstructionInfo *info, uint16_t data)
{
    if (info->dstCode == 0 && info->dstReg == 7) {
        system->writeInPSW(data);
        return;
    }
    if (info->dstCode == 0) throw WrongDstOperandError();
    if (info->dstCode == 1) system->writeInRegister(info->dstReg, data);
    else {
        system->writeWordToMemory(info->extraWord, data);

        if ((info->extraWord == system->OUT_IO_ADDRESS) && (info->dstCode != 1)) system->outputIONotify = true;
    }
}
