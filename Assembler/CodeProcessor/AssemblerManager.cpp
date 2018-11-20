//
// Created by mandula on 9.8.18..
//

#include <sstream>
#include "AssemblerManager.h"
#include "../Parser/ParserExceptions/EndOfFileException.h"
#include "Exceptions/EndDirectiveFoundException.h"
#include "../Tables/Exceptions/TableException.h"
#include "../Parser/ParserErrors/ParserError.h"

AssemblerManager::AssemblerManager()
{
    parser = NULL;
    symbolTable = NULL;
    sectionTable = NULL;
    locationCounter = NULL;
    codeGenerator = NULL;

    labelHandler = NULL;
    directiveHandler = NULL;

    zeroOperandHandler = NULL;
    oneOperandHandler = NULL;
    twoOperandsHandler = NULL;

    mnemonicTable = NULL;
    conditionTable = NULL;


    fileName = NULL;
}

void AssemblerManager::initialize(char* filePath, int locationCounterStart)
{
    parser = new Parser(filePath);
    symbolTable = new SymbolTable();
    sectionTable = new SectionTable();
    locationCounter = new LocationCounter(locationCounterStart);
    codeGenerator = new CodeGenerator();
    conditionTable = new ConditionTable();

    labelHandler = new LabelHandler(symbolTable, sectionTable, locationCounter);
    directiveHandler = new DirectiveHandler(symbolTable, sectionTable, locationCounter, codeGenerator);

    zeroOperandHandler = new ZeroOperandHandler
            (locationCounter, symbolTable, sectionTable, codeGenerator, conditionTable);
    oneOperandHandler = new OneOperandHandler
            (locationCounter, symbolTable, sectionTable, codeGenerator, conditionTable);
    twoOperandsHandler = new TwoOperandsHandler
            (locationCounter, symbolTable, sectionTable, codeGenerator, conditionTable);

    mnemonicTable = new MnemonicTable(zeroOperandHandler, oneOperandHandler, twoOperandsHandler);


    fileName = static_cast<char*>(malloc(strlen(filePath) + 1));
    strcpy(fileName, filePath);
    startAddress = locationCounterStart;
}

void AssemblerManager::doOnePass(int passNum)
{
    try {
        while (true) {
            try {
                LineElements lineElements;
                parser->parseLine(&lineElements);
                if (passNum == 1) firstPassWork(&lineElements);
                else if (passNum == 2) secondPassWork(&lineElements);
            } catch (EndOfFileException) {
                break;
            } catch (EndDirectiveFoundException) {
                break;
            }
        }
    } catch (AssemblerException e) {
        std::cout << e.what() << std::endl;
        exit(50);
    }
}

void AssemblerManager::firstPassWork(LineElements* lineElements)
{
    try {
        resolveLabelFirstPass(lineElements);
        resolveDirectiveFirstPass(lineElements);
        resolveMnemonicFirstPass(lineElements);
    } catch (TableException e) {
        std::ostringstream fullMessage;
        fullMessage << e.what() << " Line " << lineElements->getLineNumber() << "!" << std::endl;
        throw TableException(fullMessage.str().data());
    } catch (AsmException e) {
        std::ostringstream fullMessage;
        fullMessage << e.what() << " Line " << lineElements->getLineNumber() << "!" << std::endl;
        throw AsmException(fullMessage.str().data());
    }
}

void AssemblerManager::resolveLabelFirstPass(LineElements* lineElements)
{
    LineType lineType = lineElements->getLineType();
    if ((lineType == justLabelLine) || (lineType == labelMnemonicLine) || (lineType == labelDirectiveLine)) {
        labelHandler->handleLabel(lineElements->getLabel());
    }

}

void AssemblerManager::resolveDirectiveFirstPass(LineElements* lineElements)
{
    LineType lineType = lineElements->getLineType();
    if ((lineType == directiveLine) || (lineType == labelDirectiveLine)) {
        directiveHandler->handleFirstPass(lineElements);
    }
}

void AssemblerManager::resolveMnemonicFirstPass(LineElements* lineElements)
{
    LineType lineType = lineElements->getLineType();
    if ((lineType == mnemonicLine) || (lineType == labelMnemonicLine)) {
        OperandHandler* operandHandler = mnemonicTable->getOperandHandler(lineElements->getOpCode());
        operandHandler->firstPassHandleOperand(lineElements);
    }
}

void AssemblerManager::secondPassWork(LineElements* lineElements)
{
    if ((lineElements->getLineType() == none) || (lineElements->getLineType() == justLabelLine)) return;
    if ((lineElements->getLineType() == directiveLine) || (lineElements->getLineType() == labelDirectiveLine)) {
        directiveHandler->handleSecondPass(lineElements);
    }
    else { //mnemonic line
        OperandHandler* operandHandler = mnemonicTable->getOperandHandler(lineElements->getOpCode());
        operandHandler->secondPassHandleOperand(lineElements);
    }
}

void AssemblerManager::doBetweenPasses()
{
    sectionTable->notifyFileEnd(locationCounter->getLocationCounter());
    locationCounter->restartLocationCounter();
    delete(parser);
    parser = new Parser(fileName);
    //parser->reopenFile(fileName);
}

void AssemblerManager::terminate()
{
    if (parser != NULL) delete(parser);
    if (symbolTable != NULL) delete(symbolTable);
    if (sectionTable != NULL) delete(sectionTable);
    if (locationCounter != NULL) delete(locationCounter);
    if (labelHandler != NULL) delete(labelHandler);
    if (directiveHandler != NULL) delete(directiveHandler);
    if (zeroOperandHandler != NULL) delete(zeroOperandHandler);
    if (oneOperandHandler != NULL) delete(oneOperandHandler);
    if (twoOperandsHandler != NULL) delete(twoOperandsHandler);
    if (mnemonicTable != NULL) delete(mnemonicTable);
    if (conditionTable != NULL) delete(conditionTable);
    if (codeGenerator != NULL) delete(codeGenerator);
    if (fileName != NULL) delete(fileName);

    parser = NULL;
    symbolTable = NULL;
    sectionTable = NULL;
    locationCounter = NULL;
    codeGenerator = NULL;

    labelHandler = NULL;
    directiveHandler = NULL;

    zeroOperandHandler = NULL;
    oneOperandHandler = NULL;
    twoOperandsHandler = NULL;

    mnemonicTable = NULL;
    conditionTable = NULL;


    fileName = NULL;
}

void AssemblerManager::writeInFile()
{
    std::string outFile = fileName;

    for (int i = 0; i < outFile.length() - 3; ++i) {
        if ((outFile[i] == '.') &&
            (outFile[i + 1] == 't') &&
            (outFile[i + 2] == 'x') &&
            (outFile[i + 3] == 't')) {
                outFile.erase(i, outFile.length() - i);
                break;
        }
    }
    std::string outText = outFile;
    outText.append("Out.txt");
    outFile.append(".o");

    codeGenerator->createProgramTextFile(const_cast<char*>(outText.data()), symbolTable, sectionTable, startAddress);
    codeGenerator->createProgramObjFile(const_cast<char*>(outFile.data()), symbolTable, sectionTable, startAddress);
}

void AssemblerManager::assemblyFile(char* filePath, int locationCounterStart)
{
    initialize(filePath, locationCounterStart);
    doOnePass(1);
    doBetweenPasses();
    doOnePass(2);
    writeInFile();
    terminate();
}

AssemblerManager::~AssemblerManager()
{
    if (fileName != NULL) delete(fileName);
    terminate();
}
