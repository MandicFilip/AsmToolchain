#include <iostream>
#include "Linker/Linker.h"
#include "Emulator/OperationExecuter.h"
#include "Loader/Loader.h"
#include "Emulator/Emulator.h"
#include <termios.h>
#include <sys/select.h>

struct termios prev_termios;

int main(int argc, char** argv) {

    struct termios tmp;

    if (tcgetattr(fileno(stdin), &tmp) == -1){
        printf("Failed to get terminal.\n");
        exit(2);
    }

    prev_termios = tmp;
    tmp.c_lflag &= ~ECHO;
    tmp.c_lflag &= ~ICANON;
    fflush(stdout);
    if (tcsetattr(fileno(stdin), TCSANOW, &tmp) == -1){
        printf("Failed to set terminal.\n");
        exit(2);
    }

    std::string* fileNames = new std::string[argc - 1];
    for (int i = 1; i < argc; ++i) {
        fileNames[i - 1] = argv[i];
    }
    ProgramInput programInput;

    Linker linker;
    linker.linkFiles(fileNames, argc - 1, &programInput);

    System* system = new System();
    Loader loader;
    loader.loadProgram(programInput, system);

    Emulator* emulator = new Emulator(system);
    emulator->emulateProgram(&programInput);

    delete(emulator);
    delete(system);

    if (tcsetattr(fileno(stdin), TCSANOW, &prev_termios) == -1){
        printf("Failed to restore terminal.\n");
    }

    return 0;
}