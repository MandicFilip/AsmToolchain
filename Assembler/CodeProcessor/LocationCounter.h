//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_LOCATIONCOUNTERTRACER_H
#define SS_PROJECT_LOCATIONCOUNTERTRACER_H

#include <cstdint>
#include <bits/types.h>
#include "../CommonTypes/CommonTypeWrappers.h"

class LocationCounter
{
    uint16_t locationCounter;
    uint16_t startPosition;

public:
    explicit LocationCounter(uint16_t locationCounter);

    void align(uint16_t alignment);
    uint16_t getLocationCounter() const;
    void moveLocationCounter(uint16_t offset);
    void restartLocationCounter();
};


#endif //SS_PROJECT_LOCATIONCOUNTERTRACER_H
