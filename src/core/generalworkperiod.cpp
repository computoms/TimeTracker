#include "generalworkperiod.h"

GeneralWorkPeriod::GeneralWorkPeriod():
    _start       (TimeOfDay()),
    _end         (TimeOfDay())
{

}

GeneralWorkPeriod::GeneralWorkPeriod(TimeOfDay start):
    _start       (start),
    _end         (TimeOfDay())
{

}

GeneralWorkPeriod::GeneralWorkPeriod(TimeOfDay start, TimeOfDay end):
    _start   (start),
    _end     (end)
{

}

GeneralWorkPeriod::~GeneralWorkPeriod()
{

}

TimeOfDay GeneralWorkPeriod::getStart() const
{
    return _start;
}

void GeneralWorkPeriod::setStart(const TimeOfDay &value)
{
    _start = value;
}

void GeneralWorkPeriod::setStart()
{
    _start = DateTime::now().getTimeOfDay();
}

TimeOfDay GeneralWorkPeriod::getEnd() const
{
    return _end;
}

void GeneralWorkPeriod::setEnd(const TimeOfDay &value)
{
    _end = value;
}

void GeneralWorkPeriod::setEnd()
{
    _end = DateTime::now().getTimeOfDay();
}

Duration GeneralWorkPeriod::getDuration() const
{
    DateTime start(DateTime::today().getDate(), _start);
    DateTime end(DateTime::today().getDate(), _end);
    return  start.distanceTo(end);
}




