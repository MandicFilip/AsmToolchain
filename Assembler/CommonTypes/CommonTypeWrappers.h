//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_COMMONTYPEWRAPPERS_H
#define SS_PROJECT_COMMONTYPEWRAPPERS_H

#include <cstdint>
#include <exception>
#include <cstring>
#include <cstdlib>


enum LineType {none, justLabelLine, directiveLine, mnemonicLine, labelDirectiveLine, labelMnemonicLine};
enum AddressType {imm, symValue, memDir, locFromValue, regDir, regIndByValue, regIndBySym, pcRel, psw};
enum ReallocationType {absolutely, relative};

class AssemblerException : public std::exception
{
    char* _message;
protected:

    void setMessage(char* message)
    {
        strcpy(_message, message);
    }

public:
    AssemblerException()
    {
        _message = static_cast<char*>(malloc(100));
    }

    AssemblerException(const char* message)
    {
        _message = static_cast<char*>(malloc(100));
        strcpy(_message, message);
    }

    AssemblerException(const AssemblerException& parserError)
    {
        _message = static_cast<char*>(malloc(100));
        strcpy(_message, parserError.what());
    }

    virtual ~AssemblerException()
    {
        if (_message != NULL ) delete(_message);
        _message = NULL;
    }

    const char* what() const noexcept
    {
        return _message;
    }
};


#endif //SS_PROJECT_COMMONTYPEWRAPPERS_H
