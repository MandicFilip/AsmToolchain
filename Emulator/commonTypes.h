//
// Created by mandula on 18.8.18..
//

#ifndef SS_EMULATOR_COMMONTYPES_H
#define SS_EMULATOR_COMMONTYPES_H


#include <cstdint>
#include <exception>
#include <cstring>
#include <cstdlib>


enum LineType {none, justLabelLine, directiveLine, mnemonicLine, labelDirectiveLine, labelMnemonicLine};
enum AddressType {imm, symValue, memDir, locFromValue, regDir, regIndByValue, regIndBySym, pcRel, pswAddress};
enum ReallocationType {apsolutely, relative};

const uint16_t IO_SECTION_START = 65408; //65536 - 128
const uint16_t STACK_START = 65407;
const uint16_t IVT_SIZE = 16;

class MyException : public std::exception
{
    char* _message;
protected:

    void setMessage(char* message)
    {
        strcpy(_message, message);
    }

public:
    MyException()
    {
        _message = static_cast<char*>(malloc(100));
    }

    MyException(const char* message)
    {
        _message = static_cast<char*>(malloc(100));
        strcpy(_message, message);
    }

    MyException(const MyException& parserError)
    {
        _message = static_cast<char*>(malloc(100));
        strcpy(_message, parserError.what());
    }

    virtual ~MyException()
    {
        if (_message != NULL ) delete(_message);
        _message = NULL;
    }

    const char* what() const noexcept
    {
        return _message;
    }
};

#endif //SS_EMULATOR_COMMONTYPES_H
