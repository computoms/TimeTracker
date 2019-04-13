#include "timeplanner.h"

TimePlanner::TimePlanner(Duration weeklyWorkDuration):
    _weeklyWorkDuration (weeklyWorkDuration)
{

}

TimePlanner::~TimePlanner()
{

}

Duration TimePlanner::getDailyWorkDuration() const
{
    return _weeklyWorkDuration / 5.0;
}

Duration TimePlanner::getWeeklyWorkDuration() const
{
    return _weeklyWorkDuration;
}

Duration TimePlanner::getExtraTime(Duration timeWorked, int numberOfWorkingDays) const
{
    return timeWorked - (getDailyWorkDuration() * numberOfWorkingDays);
}

