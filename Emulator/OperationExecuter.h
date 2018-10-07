//
// Created by mandula on 22.8.18..
//

#ifndef SS_EMULATOR_OPERATIONEXECUTER_H
#define SS_EMULATOR_OPERATIONEXECUTER_H


#include "InstructionInfo.h"
#include "../System/System.h"

enum OperationCodes {ADD, SUB, MUL, DIV, CMP, AND, OR, NOT, TEST, PUSH, POP, CALL, IRET, MOV, SHL, SHR};
enum Conditions {EQUAL, NOT_EQUAL, GREATER_THEN, ALWAYS};

class OperationExecuter
{
protected:
    System* system;

    bool checkCondition(InstructionInfo* info);

    bool isZero(int16_t result);
    bool isOverflow(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode);
    bool isCarry(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode);
    bool isNegative(int16_t result);

    void setAllPswFlags(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode);
    void setZeroNegativeFlags(int16_t result);
    void setZeroNegativeCarryFlags(int16_t result, int16_t firstOp, int16_t secondOp, unsigned char opCode);

    void doAdd(InstructionInfo* info);
    void doSub(InstructionInfo* info);
    void doMul(InstructionInfo* info);
    void doDiv(InstructionInfo* info);
    void doCmp(InstructionInfo* info);
    void doAnd(InstructionInfo* info);
    void doOr(InstructionInfo* info);
    void doNot(InstructionInfo* info);
    void doTest(InstructionInfo* info);
    void doPush(InstructionInfo* info);
    void doPop(InstructionInfo* info);
    void doCall(InstructionInfo* info);
    void doIret(InstructionInfo* info);
    void doMov(InstructionInfo* info);
    void doShl(InstructionInfo* info);
    void doShr(InstructionInfo* info);

    int16_t getDstValue(InstructionInfo* info);
    int16_t getSrcValue(InstructionInfo* info);
    void writeResultIntoDst(InstructionInfo *info, uint16_t data);

public:
    OperationExecuter(System *system);

    void executeInstruction(InstructionInfo* info);
};


#endif //SS_EMULATOR_OPERATIONEXECUTER_H
