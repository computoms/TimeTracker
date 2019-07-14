#include "actioncontroller.h"
#include "pagegenerator.h"

ActionController::ActionController() {

}

void ActionController::initializeActions()
{
    functions[PageAddress::StartWorking] = []() { /* TODO call TimeTracker::startWorking() */};
    functions[PageAddress::StopWorking] = []() { /* TODO call TimeTracker::stopWorking() */};
    functions[PageAddress::Quit] = []() { /* TODO stop working, save to file. */ };
}

void ActionController::execute(std::string path) const
{
    if (functions.find(path) != functions.end())
        functions.at(path)();
}
