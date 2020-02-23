#include "workdaycollectionreader.h"
#include "pugixml.hpp"
#include <iostream>
#include <fstream>

WorkDayCollectionReader::WorkDayCollectionReader()
{

}

WorkDayCollectionReader::~WorkDayCollectionReader()
{

}

std::vector<std::shared_ptr<WorkDay>> WorkDayCollectionReader::read(std::string filename)
{
    std::ifstream file(filename.c_str());
    std::string content;
    content.assign(std::istreambuf_iterator<char>(file),
                   std::istreambuf_iterator<char>());
    return readFromString(content);
}

std::vector<std::shared_ptr<WorkDay>> WorkDayCollectionReader::readFromString(std::string xmlContent)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xmlContent.c_str());
    if (!result)
    {
        std::cout << "ERROR: " << result.description() << std::endl;
        return std::vector<std::shared_ptr<WorkDay>>(); // ERROR
    }

    std::vector<std::shared_ptr<WorkDay>> workDays;

    for (pugi::xml_node wd = doc.child("WorkDayCollection").child("WorkDay");
         wd; wd = wd.next_sibling("WorkDay"))
    {
        std::string dateString = wd.child("Date").child_value();
        DateTime date = DateTime::fromString(dateString);
        std::shared_ptr<WorkDay> d(std::make_shared<WorkDay>(date.getDate()));

        for (pugi::xml_node wp = wd.child("WorkPeriods").child("GeneralWorkPeriod");
             wp; wp = wp.next_sibling("GeneralWorkPeriod"))
        {
            std::string startString = wp.child("Start").child_value();
            std::string endString = wp.child("End").child_value();
            TimeOfDay start = DateTime::timeFromString(startString);
            TimeOfDay end = DateTime::timeFromString(endString);

            GeneralWorkPeriod workPeriod(start, end);
            d->addWorkPeriod(workPeriod);
        }

        for (pugi::xml_node je = wd.child("JournalEntries").child("JournalEntry");
             je; je = je.next_sibling("JournalEntry"))
        {
            std::string jeString = je.child_value();
            d->addJournalEntry(JournalEntry(jeString));
        }

        workDays.push_back(d);
    }
    return workDays;
}

