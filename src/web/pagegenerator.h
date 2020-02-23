#ifndef TT_PAGE_GENERATOR_H
#define TT_PAGE_GENERATOR_H

#include <string>
#include <map>

#include "core/timetracker.h"

class PageGenerator;

typedef std::string (*GenerateHttpPage)(const PageGenerator *pg);

/**
 * @brief The PageGenerator class manages the generation of HTTP pages as user interfaces
 * for the application.
 */
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

    // Utils
    std::string englobeInHtml(std::string content) const;
    std::string makeActionButton(std::string buttonText, std::string action) const;

    std::map<std::string, GenerateHttpPage> _pages;
    TimeTracker *_timeTracker;
};

#endif // TT_PAGE_GENERATOR_H