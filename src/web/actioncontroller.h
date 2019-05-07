#ifndef TT_ACTION_CONTROLLER_H
#define TT_ACTION_CONTROLLER_H

class ActionController
{
public:
    ActionController(); // TODO pass the TimeTracker instance here

    void startWorking() const;
    void stopWorking() const;
    void quit() const;
};

#endif // TT_ACTION_CONTROLLER_H