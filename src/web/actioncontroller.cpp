#include "actioncontroller.h"
#include "pagegenerator.h"
#include "pageaddress.h"

ActionController::ActionController(TimeTracker *tt):
    timeTracker (tt)
{

}

void ActionController::initializeActions()
{
    functions[PageAddress::StartWorking] = [](TimeTracker *timeTracker) { timeTracker->startWorking(); };
    functions[PageAddress::StopWorking] = [](TimeTracker *timeTracker) { timeTracker->stopWorking(); };
    functions[PageAddress::Quit] = [](TimeTracker *timeTracker)
            {
                if (timeTracker->isWorking())
                    timeTracker->stopWorking();
            };
}

void ActionController::execute(std::string path) const
{
    if (functions.find(path) != functions.end())
        functions.at(path)(timeTracker);
}
