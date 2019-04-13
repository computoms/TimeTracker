#include "workday.h"

WorkDay::WorkDay():
    _day                 (DateTime::today().getDate()),
    _currentWorkPeriod   (NULL)
{

}

WorkDay::WorkDay(Date d):
    _day (d),
    _currentWorkPeriod  (NULL)
{

}

WorkDay::~WorkDay()
{

}

bool WorkDay::isNull()
{
    return DateTime::areDatesEqual(_day, Date());
}

Duration WorkDay::getWorkTime() const
{
    Duration totalWorkTime;
    for (size_t i(0); i < _workPeriods.size(); ++i)
        totalWorkTime += _workPeriods[i].getDuration();

    return totalWorkTime;
}

void WorkDay::addWorkPeriod(GeneralWorkPeriod p)
{
    _workPeriods.push_back(p);
    _currentWorkPeriod = &_workPeriods.back();
}

void WorkDay::addJournalEntry(JournalEntry entry)
{
    _journalEntries.push_back(entry);
}


DateTime WorkDay::getTime() const
{
    return DateTime(_day, TimeOfDay());
}

GeneralWorkPeriod *WorkDay::getCurrentWorkPeriod() const
{
    return _currentWorkPeriod;
}



std::vector<GeneralWorkPeriod> WorkDay::getWorkPeriods() const
{
    return _workPeriods;
}

void WorkDay::setWorkPeriods(const std::vector<GeneralWorkPeriod> &workPeriods)
{
    _workPeriods = workPeriods;
}
std::vector<JournalEntry> WorkDay::getJournalEntries() const
{
    return _journalEntries;
}

void WorkDay::setJournalEntries(const std::vector<JournalEntry> &journalEntries)
{
    _journalEntries = journalEntries;
}

