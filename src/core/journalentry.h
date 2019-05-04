#ifndef JOURNALENTRY_H
#define JOURNALENTRY_H
#include <string>

/**
 * @brief The JournalEntry class represents a single entry in the "job journal"
 */
class JournalEntry
{
public:
    JournalEntry(std::string getValue);
    ~JournalEntry();

    std::string getValue() const;
    void setValue(const std::string &value);

private:
    std::string _value;
};

#endif // JOURNALENTRY_H
