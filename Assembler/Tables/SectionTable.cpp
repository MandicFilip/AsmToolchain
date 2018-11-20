//
// Created by mandula on 9.8.18..
//

#include <iostream>
#include "SectionTable.h"
#include "Exceptions/NoneSectionException.h"
#include "Exceptions/SectionAlreadyDefinedException.h"
#include "Exceptions/WrongSymbolThatRepresentsSectionException.h"
#include <sstream>

SectionTable::SectionTable() : currentSection("none"), nextSectionIndex(0)
{}

void SectionTable::insertSection(std::string section, uint16_t basicAddress)
{
    if (isSectionDefined(section)) throw SectionAlreadyDefinedException();

    if (strcmp(currentSection.data(), "none"))
        sectionTable.back().size = basicAddress - sectionTable.back().basicAddress;
    sectionTable.push_back(SectionInfo(section, basicAddress));
    currentSection = section;
}

bool SectionTable::isSectionDefined(std::string section)
{
    for (std::vector<SectionInfo>::iterator iter = sectionTable.begin(); iter != sectionTable.end(); ++iter) {
        if (!strcmp(section.data(), iter->name.data())) return true;
    }
    return false;
}

std::string SectionTable::getCurrentSection()
{
    return currentSection;
}

uint16_t SectionTable::getSectionId(std::string section)
{
    for (std::vector<SectionInfo>::iterator iter = sectionTable.begin(); iter != sectionTable.end(); ++iter) {
        if (!strcmp(section.data(), iter->name.data())) return static_cast<uint16_t>(iter - sectionTable.begin() + 1);
    }
    return 0;
}

void SectionTable::notifyFileEnd(uint16_t currentAddress)
{
    if (strcmp(sectionTable.back().name.data(), "none"))
        sectionTable.back().size = currentAddress - sectionTable.back().basicAddress;
    currentSection = "none";
    nextSectionIndex = 0;
}

uint16_t SectionTable::getSectionStartAddress(std::string section)
{
    for (std::vector<SectionInfo>::iterator iter = sectionTable.begin(); iter != sectionTable.end(); ++iter) {
        if (!strcmp(section.data(), iter->name.data())) return iter->basicAddress;
    }
    throw WrongSymbolThatRepresentsSectionException();
}

std::ostream& operator<<(std::ostream& out, SectionTable sectionTable)
{
    out << std::endl;
    out << "---Section Table---" << std::endl;
    out << "Section " << "Address " << "Size " << "Descriptor" << std::endl;

    for (std::vector<SectionTable::SectionInfo>::iterator iter = sectionTable.sectionTable.begin();
            iter != sectionTable.sectionTable.end(); ++iter) {
        unsigned long blank = 0;
        out << iter->name;
        blank = 8 - iter->name.length();
        for (int i = 0; i < blank; i++) out << " ";

        std::ostringstream ss1;
        ss1 << iter->basicAddress;
        std::string str1 = ss1.str();
        out << str1;
        blank = 8 - str1.length();
        for (int i = 0; i < blank; i++) out << " ";

        std::ostringstream ss2;
        ss2 << iter->size;
        std::string str2 = ss2.str();
        out << str2;
        blank = 5 - str2.length();
        for (int i = 0; i < blank; i++) out << " ";

        out << iter->descriptor;
        out << std::endl;
    }
    out << std::endl;

    return out;
}

uint16_t SectionTable::getSectionSize(std::string section)
{
    for (std::vector<SectionInfo>::iterator iter = sectionTable.begin(); iter != sectionTable.end(); ++iter) {
        if (!strcmp(section.data(), iter->name.data())) return iter->size;
    }
    throw WrongSymbolThatRepresentsSectionException();
}

uint16_t SectionTable::getSectionDescriptor(std::string section)
{
    for (std::vector<SectionInfo>::iterator iter = sectionTable.begin(); iter != sectionTable.end(); ++iter) {
        if (!strcmp(section.data(), iter->name.data())) return iter->descriptor;
    }
    throw WrongSymbolThatRepresentsSectionException();
}

void SectionTable::enterNextSection()
{
    if (sectionTable.size() > 0)
        currentSection = sectionTable[nextSectionIndex].name;
    nextSectionIndex++;
}
