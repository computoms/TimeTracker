#ifndef WORKDAYCOLLECTIONREADER_H
#define WORKDAYCOLLECTIONREADER_H

#include "workday.h"
#include <vector>

class WorkDayCollectionReader
{
public:
    WorkDayCollectionReader();
    ~WorkDayCollectionReader();

    std::vector<WorkDay> readFromString(std::string xmlContent);
};

#endif // WORKDAYCOLLECTIONREADER_H
