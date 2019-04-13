#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>
#include <vector>

/**
 * @brief The Date struct represents a single day in a year
 */
struct Date
{
    Date()
    {
        year = 0;
        month = 0;
        dayOfMonth = 0;
    }

    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        dayOfMonth = d;
    }

    int year;
    int month;
    int dayOfMonth;
};

/**
 * @brief The TimeOfDay struct represents a time in a day.
 */
struct TimeOfDay
{
    TimeOfDay()
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    TimeOfDay(int h, int m, int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    int hours;
    int minutes;
    int seconds;
};

class Duration;

/**
 * @brief The DateTime class represents either a given moment in time or a time duration.
 */
class DateTime
{
public:
    DateTime();
    DateTime(Date date);
    DateTime(Date date, TimeOfDay timeOfDay);
    ~DateTime();

    static DateTime now();
    static DateTime today();
    // static WeekNumber => DateTime.weekNumber

    bool isSameDayAs(DateTime d) const;
    static bool areDatesEqual(Date d1, Date d2);

    Date getDate() const;
    TimeOfDay getTimeOfDay() const;

    Duration distanceTo(DateTime a) const;

    time_t toLocalTime() const;

    std::string toString() const;
    static std::string toString(TimeOfDay const &t);
    static std::string toString(Date const &d);

    static DateTime fromString(const std::string &dateTimeAsString);
    static TimeOfDay timeFromString(const std::string &timeAsString);
    static Date dateFromString(const std::string &dateString);

private:
    static std::vector<std::string> parseString(std::string stringToParse, std::string delimiter);

    Date _date;
    TimeOfDay _time;
};

bool operator<(DateTime const &d1, DateTime const &d2);
bool operator<=(DateTime const &d1, DateTime const &d2);
bool operator>(DateTime const &d1, DateTime const &d2);
bool operator>=(DateTime const &d1, DateTime const &d2);
double getDiffTime(const DateTime &d1, const DateTime &d2);

#endif // DATETIME_H
