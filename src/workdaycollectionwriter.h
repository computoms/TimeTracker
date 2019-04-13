#ifndef WORKDAYCOLLECTIONWRITER_H
#define WORKDAYCOLLECTIONWRITER_H
#include "workday.h"
#include <vector>
#include <string>

class WorkDayCollectionWriter
{
public:
    WorkDayCollectionWriter(std::vector<WorkDay> workDayCollection);
    ~WorkDayCollectionWriter();

    void write(std::string filename) const;
    std::string writeToString() const;

private:
    std::vector<WorkDay> _workDays;
};

#endif // WORKDAYCOLLECTIONWRITER_H
