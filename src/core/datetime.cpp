#include "datetime.h"
#include "duration.h"
#include <sstream>
#include <iostream>


DateTime::DateTime()
{

}

DateTime::DateTime(Date date):
    _date   (date)
{

}

DateTime::DateTime(Date date, TimeOfDay timeOfDay):
    _date   (date),
    _time   (timeOfDay)
{

}

DateTime::~DateTime()
{

}

Duration DateTime::distanceTo(DateTime a) const
{
    double diffSeconds = getDiffTime(*this, a);
    TimeOfDay t(0, 0, diffSeconds);
    Duration dur(0, t);
    dur.rearange();
    return dur;
}

time_t DateTime::toLocalTime() const
{
    struct tm dtm1;
    dtm1.tm_year = _date.year == 0 ? 0 : _date.year - 1900;
    dtm1.tm_mon = _date.month == 0 ? 0 : _date.month - 1;
    dtm1.tm_mday = _date.dayOfMonth;
    dtm1.tm_hour = _time.hours;
    dtm1.tm_min = _time.minutes;
    dtm1.tm_sec = _time.seconds;
    dtm1.tm_wday = 0;
    dtm1.tm_yday = 0;
    dtm1.tm_isdst = -1;

    return mktime(&dtm1);
}

DateTime DateTime::now()
{
    time_t ttime = time(NULL);
    struct tm lt = (*localtime(&ttime));

    Date d;
    d.year = lt.tm_year + 1900;
    d.month = lt.tm_mon + 1;
    d.dayOfMonth = lt.tm_mday;
    TimeOfDay t;
    t.hours = lt.tm_hour;
    t.minutes = lt.tm_min;
    t.seconds = lt.tm_sec;
    return DateTime(d, t);
}

DateTime DateTime::today()
{
    time_t t = time(NULL);
    struct tm lt = (*localtime(&t));
    Date d;
    d.year = lt.tm_year + 1900;
    d.month = lt.tm_mon + 1;
    d.dayOfMonth = lt.tm_mday;
    return DateTime(d, TimeOfDay());
}

bool DateTime::isSameDayAs(DateTime d) const
{
    Date dDate = d.getDate();
    return _date.year == dDate.year && _date.month == dDate.month && _date.dayOfMonth == dDate.dayOfMonth;
}

bool DateTime::areDatesEqual(Date d1, Date d2)
{
    return d1.year == d2.year && d1.month == d2.month && d1.dayOfMonth == d2.dayOfMonth;
}

Date DateTime::getDate() const
{
    return _date;
}

TimeOfDay DateTime::getTimeOfDay() const
{
    return _time;
}

bool operator<(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) > 0;
}

bool operator<=(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) >= 0;
}

double getDiffTime(const DateTime &d1, const DateTime &d2)
{
    time_t t1 = d1.toLocalTime();
    time_t t2 = d2.toLocalTime();
    return difftime(t2, t1);
}


bool operator>(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) < 0;
}


bool operator>=(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) <= 0;
}


std::string DateTime::toString() const
{
    std::stringstream ss;
    ss << DateTime::toString(_date)
       << "_"
       << DateTime::toString(_time);
    return ss.str();
}

std::string DateTime::toString(const TimeOfDay &t)
{
    std::stringstream ss;
    ss << (t.hours < 10 ? "0" : "") << t.hours << ":"
       << (t.minutes < 10 ? "0" : "") << t.minutes << ":"
       << (t.seconds < 10 ? "0" : "") << t.seconds;
    return ss.str();
}

std::string DateTime::toString(const Date &d)
{
    std::stringstream ss;
    ss << d.year << "-"
       << (d.month < 10 ? "0" : "") << d.month << "-"
       << (d.dayOfMonth < 10 ? "0" : "") << d.dayOfMonth;
    return ss.str();
}


DateTime DateTime::fromString(const std::string &dateTimeAsString)
{
    std::vector<std::string> dateTime = parseString(dateTimeAsString, "_");
    if (dateTime.size() != 2)
        return DateTime(); // TODO ERROR

    Date d = DateTime::dateFromString(dateTime[0]);
    TimeOfDay t = DateTime::timeFromString(dateTime[1]);

    return DateTime(d, t);
}

TimeOfDay DateTime::timeFromString(const std::string &timeAsString)
{
    std::vector<std::string> timeVector = parseString(timeAsString, ":");
    if (timeVector.size() != 3)
        return TimeOfDay(); // TODO ERROR

    TimeOfDay t;
    t.hours = std::stoi(timeVector[0]);
    t.minutes = std::stoi(timeVector[1]);
    t.seconds = std::stoi(timeVector[2]);
    return t;
}

Date DateTime::dateFromString(const std::string &dateString)
{
    std::vector<std::string> dateVector = parseString(dateString, "-");
    if (dateVector.size() != 3)
        return Date(); // TODO ERROR

    Date d;
    d.year = std::stoi(dateVector[0]);
    d.month = std::stoi(dateVector[1]);
    d.dayOfMonth = std::stoi(dateVector[2]);
    return d;
}

std::vector<std::string> DateTime::parseString(std::string stringToParse, std::string delimiter)
{
    size_t pos = 0;
    std::vector<std::string> parsedStrings;
    std::string token;
    while ((pos = stringToParse.find(delimiter)) != std::string::npos)
    {
        token = stringToParse.substr(0, pos);
        parsedStrings.push_back(token);
        stringToParse.erase(0, pos + delimiter.length());
    }
    parsedStrings.push_back(stringToParse);
    return parsedStrings;
}
