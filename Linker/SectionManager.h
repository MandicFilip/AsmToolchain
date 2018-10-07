//
// Created by mandula on 19.8.18..
//

#ifndef SS_EMULATOR_SECTIONMANAGER_H
#define SS_EMULATOR_SECTIONMANAGER_H


#include <vector>
#include "LinkerStructs.h"

class SectionManager
{
    std::vector<SectionInfo> sections;

    bool isOverlapExists(SectionInfo &section1, SectionInfo &section2);

public:
    void addSection(SectionInfo& sectionInfo);
    bool areSectionsOverlap();
    void restartManager();
    const std::vector<SectionInfo> &getSections() const;
};


#endif //SS_EMULATOR_SECTIONMANAGER_H
