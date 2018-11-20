//
// Created by mandula on 9.8.18..
//

#ifndef SS_PROJECT_SECTIONTABLE_H
#define SS_PROJECT_SECTIONTABLE_H

#include <string>
#include <vector>
#include "../CommonTypes/CommonTypeWrappers.h"

class SectionTable
{
public:
    SectionTable();

    struct SectionInfo
    {
        std::string name;
        uint16_t basicAddress;
        uint16_t size;
        uint16_t descriptor; //rwx - 3 lowest bits

        SectionInfo(std::string _name, uint16_t _basicAddress) : name(_name), basicAddress(_basicAddress)
        {
            if (!strcmp(name.data(), ".text")) descriptor = 5;
            else if (!strcmp(name.data(), ".rodata")) descriptor = 2;
            else descriptor = 6;
        }
    };

    void insertSection(std::string section, uint16_t basicAddress);
    std::string getCurrentSection();
    uint16_t getSectionId(std::string section);
    void notifyFileEnd(uint16_t currentAddress);
    uint16_t getSectionStartAddress(std::string section);
    uint16_t getSectionSize(std::string section);
    uint16_t getSectionDescriptor(std::string section);
    void enterNextSection();

    friend std::ostream& operator<<(std::ostream& out, SectionTable sectionTable);

private:
    bool isSectionDefined(std::string section);
    std::vector<SectionInfo> sectionTable;
    std::string currentSection;

    int nextSectionIndex;
};


#endif //SS_PROJECT_SECTIONTABLE_H
