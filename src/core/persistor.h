#ifndef TT_PERSISTOR_H
#define TT_PERSISTOR_H
#include <string>

class TimeTracker;

/**
 * @brief Helper class to save the state of the TimeTracker class.
 */
class Persistor
{
public:
    virtual void save(TimeTracker *tt) const = 0;
    virtual void read(TimeTracker *tt) const = 0;
};

/**
 * @brief Persistance class to a file on the file system, using XML format.
 */
class FilePersistor : public Persistor
{
public:
    FilePersistor(std::string filename);

    virtual void save(TimeTracker *tt) const;
    virtual void read(TimeTracker *tt) const;

private:
    std::string _filename;
};


#endif // TT_PERSISTOR_H