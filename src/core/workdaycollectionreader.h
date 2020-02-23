#ifndef WORKDAYCOLLECTIONREADER_H
#define WORKDAYCOLLECTIONREADER_H

#include "workday.h"
#include <vector>

/**
 * @brief The WorkDayCollectionReader handles reading the persistence data from an xml source.
 */
class WorkDayCollectionReader
{
public:
    WorkDayCollectionReader();
    ~WorkDayCollectionReader();

    std::vector<std::shared_ptr<WorkDay>> read(std::string filename);
    std::vector<std::shared_ptr<WorkDay>> readFromString(std::string xmlContent);
};

#endif // WORKDAYCOLLECTIONREADER_H
