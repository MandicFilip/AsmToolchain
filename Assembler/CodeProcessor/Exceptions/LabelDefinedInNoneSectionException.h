//
// Created by mandula on 12.8.18..
//

#ifndef SS_PROJECT_LABELDEFINEDINNONESECTIONEXCEPTION_H
#define SS_PROJECT_LABELDEFINEDINNONESECTIONEXCEPTION_H


#include "AsmException.h"

class LabelDefinedInNoneSectionException : public AsmException
{
public:
    LabelDefinedInNoneSectionException()
    {
        setMessage(const_cast<char*>("Error! Label is defined outside of any section!"));
    }

};


#endif //SS_PROJECT_LABELDEFINEDINNONESECTIONEXCEPTION_H
