#ifndef TT_PAGE_GENERATOR_H
#define TT_PAGE_GENERATOR_H

#include <string>

class PageGenerator
{
public:
    PageGenerator();

    std::string mainPage() const;
    std::string startWorkingPage() const;
    std::string quitPage() const;
    std::string pageNotFound(std::string path) const;

private:
    std::string englobeInHtml(std::string content) const;
};

#endif // TT_PAGE_GENERATOR_H