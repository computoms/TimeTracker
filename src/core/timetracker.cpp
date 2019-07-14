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
    std::shared_ptr<WorkDay> existing = getWorkDay(DateTime::today().getDate());
    if (existing->isNull())
    {
        existing = std::shared_ptr<WorkDay>(new WorkDay(DateTime::today().getDate()));
        addWorkDay(existing);
    }

    existing->addWorkPeriod(GeneralWorkPeriod(DateTime::now().getTimeOfDay()));
}

void TimeTracker::stopWorking()
{
    std::shared_ptr<WorkDay> existing = getWorkDay(DateTime::today().getDate());
    if (!existing->isNull() && existing->getCurrentWorkPeriod() != nullptr)
    {
        existing->getCurrentWorkPeriod()->setEnd();
    }
}

void TimeTracker::addWorkDay(std::shared_ptr<WorkDay> wd)
{
    _workDays.push_back(wd);
}

bool TimeTracker::replaceWorkDay(std::shared_ptr<WorkDay> wd, Date d)
{
    int index = getWorkDayIndex(d);
    if (index == -1)
        return false;

    _workDays[index] = wd;
    return true;
}

Duration TimeTracker::getWorkingDurationOfToday() const
{
    auto existing = getWorkDay(DateTime::today().getDate());
    if (!existing->isNull())
        return existing->getWorkTime();

    return Duration();
}

Duration TimeTracker::getWorkingDurationBetween(DateTime from, DateTime to) const
{
    Duration workDuration;
    for (size_t i(0); i < _workDays.size(); ++i)
    {
        auto d = _workDays[i];
        if (d->getTime() >= from && d->getTime() <= to)
            workDuration += d->getWorkTime();
    }
    return workDuration;
}

/**
 * @brief Gets the workday at specified date.
 * @param day
 * @return
 */
std::shared_ptr<WorkDay> TimeTracker::getWorkDay(Date day) const
{
    int index = getWorkDayIndex(day);
    if (index == -1)
        return std::shared_ptr<WorkDay>(new WorkDay(Date()));
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
        if (_workDays[i]->getTime().isSameDayAs(DateTime(day, TimeOfDay())))
            return i;
    return -1;
}

bool TimeTracker::isWorking() const
{
    auto existing = getWorkDay(DateTime::today().getDate());
    if (existing->isNull())
        return false;
    return existing->getCurrentWorkPeriod() != nullptr;
}

std::vector<std::shared_ptr<WorkDay> > TimeTracker::getWorkDays() const
{
    return _workDays;
}

