#ifndef TT_ACTION_CONTROLLER_H
#define TT_ACTION_CONTROLLER_H

#include <map>
#include <memory>

// Defines a function that executes an action in the back-end
typedef void (*ActionFunction)();

class ActionController
{
public:
    ActionController(); // TODO pass the TimeTracker instance here

    void initializeActions();

    void execute(std::string path) const;

private:
    std::map<std::string, ActionFunction> functions;
};

#endif // TT_ACTION_CONTROLLER_H