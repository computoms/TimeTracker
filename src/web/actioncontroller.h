#ifndef TT_ACTION_CONTROLLER_H
#define TT_ACTION_CONTROLLER_H

#include <map>
#include <memory>
#include "core/timetracker.h"

// Defines a function that executes an action in the back-end
typedef void (*ActionFunction)(TimeTracker *timeTracker);

class ActionController
{
public:
    ActionController(TimeTracker *tt);

    void initializeActions();

    void execute(std::string path) const;

private:
    std::map<std::string, ActionFunction> functions;
    TimeTracker *timeTracker;
};

#endif // TT_ACTION_CONTROLLER_H