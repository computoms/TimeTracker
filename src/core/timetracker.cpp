#include "timetracker.h"
#include "duration.h"

TimeTracker::TimeTracker(Persistor *persistor):
    _persistor  (persistor)
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::load()
{
    _persistor->read(this);
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
    _persistor->save(this);
}

void TimeTracker::stopWorking()
{
    std::shared_ptr<WorkDay> existing = getWorkDay(DateTime::today().getDate());
    if (!existing->isNull() && existing->getCurrentWorkPeriod() != nullptr)
    {
        existing->getCurrentWorkPeriod()->setEnd();
    }
    _persistor->save(this);
}

void TimeTracker::addWorkDay(std::shared_ptr<WorkDay> wd)
{
    _workDays.push_back(wd);
    _persistor->save(this);
}

bool TimeTracker::replaceWorkDay(std::shared_ptr<WorkDay> wd, Date d)
{
    int index = getWorkDayIndex(d);
    if (index == -1)
        return false;

    _workDays[index] = wd;
    _persistor->save(this);
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

