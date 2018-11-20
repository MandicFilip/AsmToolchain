//
// Created by mandula on 22.8.18..
//

#include "InterruptHandler.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <sys/select.h>


InterruptHandler::InterruptHandler(System *system) : system(system)
{
    timer = clock();
    instructionError = false;
}

InterruptHandler::~InterruptHandler()
{}

bool InterruptHandler::isNextCharReady()
{
    int stdIn= fileno(stdin);
    struct timeval tv;

    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&fds);
    FD_SET(stdIn, &fds); //stdIn is 0

    select(stdIn+1, &fds, NULL, NULL, &tv);

    // return 0 if STDIN is not ready to be read.
    return FD_ISSET(stdIn, &fds);
}

void InterruptHandler::checkInputDevice()
{
    char c;
    if (isNextCharReady()) {
        c = static_cast<char>(getchar());
        system->writeByteToMemory(system->IN_IO_ADDRESS, c);
        system->setInterrupt(system->INPUT_ROUTINE);
    }
}

void InterruptHandler::checkOutputDevice()
{
    if (system->outputIONotify){
        system->outputIONotify = false;

        char c = system->readByteFromMemory(system->OUT_IO_ADDRESS);
        if (c == 0x10) write(STDOUT_FILENO, "\n", 1);
        else  write(STDOUT_FILENO, &c, 1);
    }

}

void InterruptHandler::checkTimer()
{
    clock_t currentTime = clock();
    if ((currentTime - timer) / CLOCKS_PER_SEC > system->TIMER_PERIOD) {
        timer = currentTime;
        uint16_t mask = 1;
        mask <<= system->TIMER_PSW_BIT;
        if (mask & system->readPSW()) {
            system->setInterrupt(system->TIMER_ROUTINE);
        }

    }

}

void InterruptHandler::handleInterrupt()
{
    checkTimer();
    checkInputDevice();
    int index = 0;
    if (!instructionError) checkOutputDevice();
    else index = system->ILLEGAL_INSTRUCTION_ROUTINE;

    uint16_t mask = 1;
    mask <<= system->INTERRUPT_PSW_BIT;

    if (mask & system->readPSW()) {
        while (index < system->INTERRUPTS_NUMBER) {
            if (system->isInterrupt(index)) {
                goToInterrupt(index);
                system->resetInterrupt(index);
                break;
            }
            index++;
        }

        if ((index == system->INTERRUPTS_NUMBER) && (instructionError)) {
            index = 0;
            while (index < system->ILLEGAL_INSTRUCTION_ROUTINE) {
                if (system->isInterrupt(index)) {
                    goToInterrupt(index);
                    system->resetInterrupt(index);
                    break;
                }
                index++;
            }
        }
    }
    instructionError = false;
}

void InterruptHandler::setInstruction_error()
{
    InterruptHandler::instructionError = true;
}

void InterruptHandler::goToInterrupt(int entry)
{
    entry *= 2; //entry size = 2
    uint16_t address = system->readWordFromMemory(entry);
    uint16_t oldPC = system->readPC();
    uint16_t oldPSW = system->readPSW();

    system->pushWordToStack(oldPC);
    system->pushWordToStack(oldPSW);

    uint16_t mask = -1;
    mask ^= (1 << 15);
    uint16_t newPsw = mask & oldPSW;
    system->writeInPSW(newPsw);
    system->writeInPC(address);
}
