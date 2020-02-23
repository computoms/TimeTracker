#ifndef TT_ACTION_CONTROLLER_H
#define TT_ACTION_CONTROLLER_H

#include <map>
#include <memory>
#include "core/timetracker.h"

// Defines a function that executes an action in the back-end
typedef void (*ActionFunction)(TimeTracker *timeTracker);

/**
 * @brief The ActionController manages the transitions (and actions)
 * performed within the application's UI. 
 */
class ActionController
{
public:
    ActionController(TimeTracker *tt);

    void initializeActions();

    void execute(std::string path) const;

private:
    std::map<std::string, ActionFunction> _functions;
    TimeTracker *_timeTracker;
};

#endif // TT_ACTION_CONTROLLER_H