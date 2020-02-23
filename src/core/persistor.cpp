#include "workdaycollectionwriter.h"
#include "workdaycollectionreader.h"
#include "timetracker.h"

FilePersistor::FilePersistor(std::string filename):
    _filename       (filename)
{

}

void FilePersistor::save(TimeTracker *tt) const
{
    WorkDayCollectionWriter writer(tt->getWorkDays());
    writer.write(_filename);
}

void FilePersistor::read(TimeTracker *tt) const
{
    WorkDayCollectionReader reader;
    auto workDays = reader.read(_filename);
    for (auto const &wd : workDays)
    {
        tt->addWorkDay(wd);
    }  
}