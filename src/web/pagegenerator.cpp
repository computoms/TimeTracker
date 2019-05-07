#include "pagegenerator.h"

PageGenerator::PageGenerator()
{

}

std::string PageGenerator::mainPage() const
{
    return englobeInHtml("<form action=\"/start-working\">"
           "    <input type=\"submit\" value=\"Start working\" />"
           "</form>"
           "<form action=\"/quit\">"
           "    <input type=\"submit\" value=\"Quit\" />"
           "</form>");
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
