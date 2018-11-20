//
// Created by mandula on 29.7.18..
//

#ifndef SS_PROJECT_PARSERSTATE_H
#define SS_PROJECT_PARSERSTATE_H

#include "../TransferObjects/LineElements.h"

class ParserState
{
    bool labelAllowed;
    bool directiveAllowed;
    bool mnemonicAllowed;
    bool operandAllowed;
    bool directiveInfoAllowed;

    bool commaAllowed;
    bool lineEndAllowed;

    LineType lineType;

public:

    void mnemonicFound();
    void operandFound();
    void directiveInfoFound();
    ParserState();
    virtual ~ParserState();

    void prepareForNextLine();

    void labelFound();
    void directiveFound();

    void commaFound();
    void lineEndFound();

    LineType getLineType() const;

};


#endif //SS_PROJECT_PARSERSTATE_H
