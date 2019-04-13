#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <vector>
#include "workday.h"

/**
 * @brief The TimeTracker class handles the registration and retreival of working times.
 */
class TimeTracker
{
public:
    TimeTracker();
    ~TimeTracker();

    void startWorking();
    void stopWorking();

    void addWorkDay(WorkDay wd);
    bool replaceWorkDay(WorkDay wd, Date d);

    Duration getWorkingDurationOfToday() const;
    Duration getWorkingDurationBetween(DateTime from, DateTime to) const;

    WorkDay getWorkDay(Date day) const;

private:
    std::vector<WorkDay> _workDays;

    size_t getWorkDayIndex(Date day) const;
};

#endif // TIMETRACKER_H
