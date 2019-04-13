#ifndef GENERALWORKPERIOD_H
#define GENERALWORKPERIOD_H

#include "datetime.h"
#include "duration.h"

/**
 * @brief The GeneralWorkPeriod class represents a working period with start and end time, within a single day.
 */
class GeneralWorkPeriod
{
public:
    GeneralWorkPeriod();
    GeneralWorkPeriod(TimeOfDay start);
    GeneralWorkPeriod(TimeOfDay start, TimeOfDay end);
    ~GeneralWorkPeriod();

    TimeOfDay getStart() const;
    void setStart(const TimeOfDay &value);
    void setStart();

    TimeOfDay getEnd() const;
    void setEnd(const TimeOfDay &value);
    void setEnd();

    Duration getDuration() const;

private:
    TimeOfDay _start;
    TimeOfDay _end;
};

#endif // GENERALWORKPERIOD_H
