#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <vector>
#include <memory>
#include "workday.h"
#include "persistor.h"

/**
 * @brief The TimeTracker class handles the registration and retreival of working times.
 */
class TimeTracker
{
public:
    TimeTracker(Persistor *persistor);
    ~TimeTracker();

    void startWorking();
    void stopWorking();

    bool isWorking() const;

    void addWorkDay(std::shared_ptr<WorkDay> wd);
    bool replaceWorkDay(std::shared_ptr<WorkDay> wd, Date d);

    Duration getWorkingDurationOfToday() const;
    Duration getWorkingDurationBetween(DateTime from, DateTime to) const;

    std::shared_ptr<WorkDay> getWorkDay(Date day) const;

    std::vector<std::shared_ptr<WorkDay> > getWorkDays() const;

private:
    std::vector<std::shared_ptr<WorkDay> > _workDays;
    Persistor *_persistor;

    size_t getWorkDayIndex(Date day) const;
};

#endif // TIMETRACKER_H
