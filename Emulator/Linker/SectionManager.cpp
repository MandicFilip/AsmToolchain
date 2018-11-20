//
// Created by mandula on 19.8.18..
//

#include "SectionManager.h"

void SectionManager::addSection(SectionInfo &sectionInfo) {
    sections.push_back(sectionInfo);
}

bool SectionManager::areSectionsOverlap() { //O(n*n) - expected small programs
    for (std::vector<SectionInfo>::iterator iter = sections.begin();iter  != sections.end(); ++iter) {
        std::vector<SectionInfo>::iterator innerIter = iter;
        innerIter++;
        while (innerIter != sections.end()) {
            if (isOverlapExists(*iter, *innerIter)) return true;
            innerIter++;
        }
    }
    return false;
}

bool SectionManager::isOverlapExists(SectionInfo &section1, SectionInfo &section2) {
    int16_t section1Start = section1.startAddress;
    int16_t section1End = section1.startAddress + section1.size;
    int16_t section2Start = section2.startAddress;
    int16_t section2End = section2.startAddress + section2.size;
    if ((section1Start >= section2Start) && (section1Start < section2End)) return true;
    if ((section2Start >= section1Start) && (section2Start < section1End)) return true;
    return false;
}

const std::vector<SectionInfo> &SectionManager::getSections() const {
    return sections;
}

void SectionManager::restartManager()
{
    sections.clear();
}
