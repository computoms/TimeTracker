#include "duration.h"
#include <cmath>

Duration::Duration():
    _days   (0)
{

}

Duration::Duration(int days, TimeOfDay t):
    _time   (t),
    _days   (days)
{
    rearange();
}

Duration::~Duration()
{

}

int Duration::getDays() const
{
    return _days;
}

int Duration::getHours() const
{
    return _time.hours;
}

int Duration::getMinutes() const
{
    return _time.minutes;
}

int Duration::getSeconds() const
{
    return _time.seconds;
}

double Duration::getTotalHours() const
{
    TimeOfDay t = _time;
    return _days * 24.0 + (double)t.hours + ((double)t.minutes / 60.0) + ((double)t.seconds / 3600.0);
}

/**
 * @brief Rearranges the duration in days, months, years, hours, minutes, seconds...
 * @param dur
 */
void Duration::rearange()
{
    double totalSeconds = getTotalSeconds();
    double oneMinuteInSeconds = 60.0;
    double oneHourInSeconds = 60.0 * oneMinuteInSeconds;
    double oneDayInSeconds = 24.0 * oneHourInSeconds;


    _days = std::floor(totalSeconds / oneDayInSeconds);
    int daysInSeconds = _days * oneDayInSeconds;

    _time.hours = std::floor((totalSeconds - daysInSeconds) / oneHourInSeconds);
    int hoursInSeconds = _time.hours * oneHourInSeconds;

    _time.minutes = std::floor((totalSeconds - daysInSeconds - hoursInSeconds) / oneMinuteInSeconds);
    int minutesInSeconds = _time.minutes * oneMinuteInSeconds;

    _time.seconds = std::floor(
                totalSeconds - daysInSeconds - hoursInSeconds - minutesInSeconds);
}

Duration &Duration::operator+=(const Duration &dur)
{
    *this = (*this + dur);
    return *this;
}

double Duration::getTotalSeconds() const
{
    return (double)(_days * 24.0 * 3600.0 + _time.hours * 3600.0 + _time.minutes * 60.0 + (double)_time.seconds);
}



Duration operator/(const Duration &dur, const double &divid)
{
    return createDurationFromSeconds(dur.getTotalSeconds() / divid);
}


Duration operator*(const Duration &dur, const double &mul)
{
    return createDurationFromSeconds(dur.getTotalSeconds() * mul);
}


Duration operator+(const Duration &dur1, const Duration &dur2)
{
    return createDurationFromSeconds(dur1.getTotalSeconds() + dur2.getTotalSeconds());
}


Duration operator-(const Duration &dur1, const Duration &dur2)
{
    return createDurationFromSeconds(dur1.getTotalSeconds() - dur2.getTotalSeconds());
}


Duration createDurationFromSeconds(int seconds)
{
    Duration d(0, TimeOfDay(0, 0, seconds));
    d.rearange();
    return d;
}
