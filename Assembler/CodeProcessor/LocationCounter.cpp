//
// Created by mandula on 9.8.18..
//

#include "LocationCounter.h"
#include "Exceptions/LCOverflowException.h"

LocationCounter::LocationCounter(uint16_t locationCounter) :
        locationCounter(locationCounter), startPosition(locationCounter)
{}

void LocationCounter::moveLocationCounter(const uint16_t offset)
{
    locationCounter += offset;
    if (locationCounter < startPosition) throw LCOverflowException();
}

void LocationCounter::restartLocationCounter()
{
    locationCounter = startPosition;
}

uint16_t LocationCounter::getLocationCounter() const
{
    return locationCounter;
}

void LocationCounter::align(uint16_t alignment)
{
    uint16_t passedSize = 0;
    if (alignment && (passedSize = locationCounter % alignment))
        locationCounter += alignment - passedSize;
}
