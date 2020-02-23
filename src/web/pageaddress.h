#ifndef TT_PAGE_ADDRESS_H
#define TT_PAGE_ADDRESS_H

#include <string>

/**
 * @brief The PageAddress class is a static class listing the 
 * valid pages of the application's UI.
 */
class PageAddress
{
public:
    static std::string Quit;
    static std::string Main;
    static std::string StartWorking;
    static std::string StopWorking;
};


#endif // TT_PAGE_ADDRESS_H