#ifndef TT_PAGE_GENERATOR_H
#define TT_PAGE_GENERATOR_H

#include <string>
#include <map>

#include "core/timetracker.h"

class PageAddress
{
public:
    static std::string Quit;
    static std::string Main;
    static std::string StartWorking;
    static std::string StopWorking;
};

class PageGenerator;

typedef std::string (*GenerateHttpPage)(const PageGenerator *pg);

class PageGenerator
{
public:
    PageGenerator(TimeTracker *tt);

    void initialize();

    std::string getPage(std::string address) const;

private:
    std::string mainPage() const;
    std::string startWorkingPage() const;
    std::string quitPage() const;
    std::string pageNotFound(std::string path) const;

    std::string englobeInHtml(std::string content) const;

    std::map<std::string, GenerateHttpPage> pages;
    TimeTracker *timeTracker;
};

#endif // TT_PAGE_GENERATOR_H