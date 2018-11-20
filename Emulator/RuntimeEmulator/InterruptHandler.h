//
// Created by mandula on 22.8.18..
//

#ifndef SS_EMULATOR_INTERRUPTHANDLER_H
#define SS_EMULATOR_INTERRUPTHANDLER_H


#include "../System/System.h"
#include <ctime>
#include <termios.h>
#include <unistd.h>

class InterruptHandler
{
    System* system;
    clock_t timer;

    bool instructionError;

    struct termios normalTerminal;
    struct termios projectTerminal;

    void setTerminal();
    void restoreNormalTerminal();

    bool isNextCharReady();

public:
    InterruptHandler(System *system);

    virtual ~InterruptHandler();

    void checkInputDevice();
    void checkOutputDevice();
    void checkTimer();
    void handleInterrupt();

    void setInstruction_error();

    void goToInterrupt(int entry);
};


#endif //SS_EMULATOR_INTERRUPTHANDLER_H
