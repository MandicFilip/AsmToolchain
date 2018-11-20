#include <iostream>
#include <cstdlib>
#include "Parser/Parser.h"
#include "Parser/ParserExceptions/EndOfFileException.h"
#include "CodeProcessor/LocationCounter.h"
#include "CodeProcessor/CodeGenerator.h"
#include "CodeProcessor/AssemblerManager.h"
#include <fstream>
#include <cmath>

int main(int argc, char** argv)
{
    if (argc < 0 || !(argc & 1)) {
        std::cout << "Error! Wrong number of parametars!";
        return -1;
    }

    for (int i = 0; i < argc / 2; ++i) {
        uint16_t location = atoi(argv[i * 2 + 1]);
        char* sourceFile = argv[i * 2+ 2];
        AssemblerManager manager;
        manager.assemblyFile(sourceFile, location);
    }

    return 0;
}