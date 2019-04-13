#include "journalentry.h"

JournalEntry::JournalEntry(std::string value):
    _value  (value)
{

}

JournalEntry::~JournalEntry()
{

}


std::string JournalEntry::getValue() const
{
    return _value;
}

void JournalEntry::setValue(const std::string &value)
{
    _value = value;
}
