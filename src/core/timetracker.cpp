#include "timetracker.h"
#include "duration.h"

TimeTracker::TimeTracker()
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::startWorking()
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (existing.isNull())
    {
        existing = WorkDay(DateTime::today().getDate());
        addWorkDay(existing);
    }

    existing.addWorkPeriod(GeneralWorkPeriod(DateTime::now().getTimeOfDay()));
}

void TimeTracker::stopWorking()
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (!existing.isNull() && existing.getCurrentWorkPeriod() != NULL)
    {
        existing.getCurrentWorkPeriod()->setEnd();
    }
}

void TimeTracker::addWorkDay(WorkDay wd)
{
    _workDays.push_back(wd);
}

bool TimeTracker::replaceWorkDay(WorkDay wd, Date d)
{
    int index = getWorkDayIndex(d);
    if (index == -1)
        return false;

    _workDays[index] = wd;
    return true;
}

Duration TimeTracker::getWorkingDurationOfToday() const
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (!existing.isNull())
        return existing.getWorkTime();

    return Duration();
}

Duration TimeTracker::getWorkingDurationBetween(DateTime from, DateTime to) const
{
    Duration workDuration;
    for (size_t i(0); i < _workDays.size(); ++i)
    {
        WorkDay d = _workDays[i];
        if (d.getTime() >= from && d.getTime() <= to)
            workDuration += d.getWorkTime();
    }
    return workDuration;
}

/**
 * @brief Gets the workday at specified date.
 * @param day
 * @return
 */
WorkDay TimeTracker::getWorkDay(Date day) const
{
    int index = getWorkDayIndex(day);
    if (index == -1)
        return WorkDay(Date());
    return _workDays[index];
}

/**
 * @brief Gets index of the workday specified by date. If it does not exist,
 * -1 is returned.
 * @param day   Date of the workday.
 * @return -1 if not found, index of the workday otherwise.
 */
size_t TimeTracker::getWorkDayIndex(Date day) const
{
    for (size_t i(0); i < _workDays.size(); ++i)
        if (_workDays[i].getTime().isSameDayAs(DateTime(day, TimeOfDay())))
            return i;
    return -1;
}

