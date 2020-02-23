#include "actioncontroller.h"
#include "pagegenerator.h"
#include "pageaddress.h"

ActionController::ActionController(TimeTracker *tt):
    _timeTracker (tt)
{

}

void ActionController::initializeActions()
{
    _functions[PageAddress::StartWorking] = [](TimeTracker *timeTracker) { timeTracker->startWorking(); };
    _functions[PageAddress::StopWorking] = [](TimeTracker *timeTracker) { timeTracker->stopWorking(); };
    _functions[PageAddress::Quit] = [](TimeTracker *timeTracker)
            {
                if (timeTracker->isWorking())
                    timeTracker->stopWorking();
            };
}

void ActionController::execute(std::string path) const
{
    if (_functions.find(path) != _functions.end())
        _functions.at(path)(_timeTracker);
}
