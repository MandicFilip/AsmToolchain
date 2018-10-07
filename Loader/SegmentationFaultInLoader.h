//
// Created by mandula on 20.8.18..
//

#ifndef SS_EMULATOR_SEGMENTATIONFAULT_H
#define SS_EMULATOR_SEGMENTATIONFAULT_H


#include "../commonTypes.h"

class SegmentationFaultInLoader : public MyException
{
public:
    SegmentationFaultInLoader()
    {
        setMessage(const_cast<char *>("Code has been tried to load in area for system data"));
    }

    virtual ~SegmentationFaultInLoader() {};
};


#endif //SS_EMULATOR_SEGMENTATIONFAULT_H
