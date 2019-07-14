#include "pagegenerator.h"

std::string PageAddress::Quit = "/quit?";
std::string PageAddress::Main = "/";
std::string PageAddress::StartWorking = "/start-working?";
std::string PageAddress::StopWorking = "/stop-working?";

PageGenerator::PageGenerator(TimeTracker *tt):
    timeTracker (tt)
{

}

std::string PageGenerator::mainPage() const
{
    std::string page = "<form action=\"/start-working\">"
                  "    <input type=\"submit\" value=\"Start working\" />"
                  "</form>"
                  "<form action=\"/quit\">"
                  "    <input type=\"submit\" value=\"Quit\" />"
                  "</form>";
    auto workDays = timeTracker->getWorkDays();
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


    return englobeInHtml(page);
}

std::string PageGenerator::englobeInHtml(std::string content) const
{
    return "<html><head><title>Time Tracker</title></head><body>"
           + content + "</body></html>";
}

std::string PageGenerator::startWorkingPage() const
{
    return englobeInHtml(
            "<form action=\"/stop-working\">"
            "    <input type=\"submit\" value=\"Stop working\" />"
            "</form>"
            "<form action=\"/quit\">"
            "    <input type=\"submit\" value=\"Quit\" />"
            "</form>");
}

std::string PageGenerator::quitPage() const
{
    return englobeInHtml("Application has been closed.");
}

std::string PageGenerator::pageNotFound(std::string path) const
{
    return englobeInHtml("<p>You requested the page '" + path + "'.</p>"
                                                                "<form action=\"\"><input type=\"submit\" value=\"Go to Main\" /></form>");
}

void PageGenerator::initialize()
{
    // Generate known pages
    pages[PageAddress::Main] = [] (const PageGenerator *pg) -> std::string { return pg->mainPage(); };
    pages[PageAddress::StartWorking] = [] (const PageGenerator *pg) -> std::string { return pg->startWorkingPage(); };
    pages[PageAddress::StopWorking] = [] (const PageGenerator *pg) -> std::string { return pg->mainPage(); };
    pages[PageAddress::Quit] = [] (const PageGenerator *pg) -> std::string { return pg->quitPage(); };
}

std::string PageGenerator::getPage(std::string address) const
{
    if (pages.find(address) == pages.end())
        return pageNotFound(address);
    return pages.at(address)(this);
}
