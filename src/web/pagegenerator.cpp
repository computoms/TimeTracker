#include "pagegenerator.h"
#include "pageaddress.h"

PageGenerator::PageGenerator(TimeTracker *tt):
    _timeTracker (tt)
{

}

void PageGenerator::initialize()
{
    // Generate known pages
    _pages[PageAddress::Main] = [] (const PageGenerator *pg) -> std::string { return pg->mainPage(); };
    _pages[PageAddress::StartWorking] = [] (const PageGenerator *pg) -> std::string { return pg->startWorkingPage(); };
    _pages[PageAddress::StopWorking] = [] (const PageGenerator *pg) -> std::string { return pg->mainPage(); };
    _pages[PageAddress::Quit] = [] (const PageGenerator *pg) -> std::string { return pg->quitPage(); };
}

std::string PageGenerator::getPage(std::string address) const
{
    if (_pages.find(address) == _pages.end())
        return pageNotFound(address);
    return englobeInHtml(
        _pages.at(address)(this));
}

//
// Pages
//

std::string PageGenerator::mainPage() const
{
    std::string page = makeActionButton("Start working", "start-working") + makeActionButton("Quit", "quit");
    auto workDays = _timeTracker->getWorkDays();
    for (auto &wd : workDays)
    {
        page += "<div>Work day " + wd->getTime().toString() + "<br/>";
        for (auto &wp : wd->getWorkPeriods())
        {
            page += std::string("<p>Work period: ") + std::to_string(wp.getDuration().getHours())
                    + "h, " + std::to_string(wp.getDuration().getMinutes()) + "m,</p>";
        }
        page += "</div>";
    }


    return page;
}

std::string PageGenerator::startWorkingPage() const
{
    return makeActionButton("Stop working", "stop-working") + makeActionButton("Quit", "quit");
}

std::string PageGenerator::quitPage() const
{
    return "Application has been closed.";
}

std::string PageGenerator::pageNotFound(std::string path) const
{
    return "<p>Page not found. <br/>You requested the page '" + path + "'.</p>"
        + makeActionButton("Go to main", "");
}

// 
// Utilities
//

std::string PageGenerator::englobeInHtml(std::string content) const
{
    return "<html><head><title>Time Tracker</title></head><body>"
           + content + "</body></html>";
}

std::string PageGenerator::makeActionButton(std::string buttonText, std::string action) const
{
    return "<form action=\"/" + action + "\">    <input type=\"submit\" value=\"" + buttonText + "\" /></form>";
}
