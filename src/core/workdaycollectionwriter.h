#ifndef WORKDAYCOLLECTIONWRITER_H
#define WORKDAYCOLLECTIONWRITER_H
#include "workday.h"
#include <vector>
#include <string>

/**
 * @brief The WorkDayCollectionWriter handles the persistence of the TimeTracker class to an xml store.
 */
class WorkDayCollectionWriter
{
public:
    WorkDayCollectionWriter(std::vector<std::shared_ptr<WorkDay>> workDayCollection);
    ~WorkDayCollectionWriter();

    void write(std::string filename) const;
    std::string writeToString() const;

private:
    std::vector<std::shared_ptr<WorkDay>> _workDays;
};

#endif // WORKDAYCOLLECTIONWRITER_H
