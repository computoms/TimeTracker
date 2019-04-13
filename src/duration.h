#ifndef DURATION_H
#define DURATION_H

#include "datetime.h"

/**
 * @brief The Duration class represents a time duration.
 */
class Duration
{
public:
    Duration();
    Duration(int days, TimeOfDay t);
    ~Duration();

    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;

    double getTotalHours() const;
    double getTotalSeconds() const;

    void rearange();

    Duration &operator+=(Duration const& dur);

private:
    TimeOfDay _time;
    int _days;

};

Duration operator/(Duration const &dur, double const &divid);
Duration operator*(Duration const &dur, double const &divid);
Duration operator+(Duration const &dur1, Duration const &dur2);
Duration operator-(Duration const &dur1, Duration const &dur2);

Duration createDurationFromSeconds(int seconds);

#endif // DURATION_H
