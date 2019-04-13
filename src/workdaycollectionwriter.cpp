#include "workdaycollectionwriter.h"
#include "../libs/pugixml/pugixml.hpp"

struct xml_string_writer: pugi::xml_writer
{
    std::string result;

    virtual void write(const void *data, size_t size)
    {
        result.append(static_cast<const char*>(data), size);
    }
};

WorkDayCollectionWriter::WorkDayCollectionWriter(std::vector<WorkDay> workDayCollection):
    _workDays   (workDayCollection)
{

}

WorkDayCollectionWriter::~WorkDayCollectionWriter()
{

}

void WorkDayCollectionWriter::write(std::string filename) const
{
    std::string xmlString = writeToString();
    pugi::xml_document doc;
    doc.load_string(xmlString.c_str());
    doc.save_file(filename.c_str());
}

std::string WorkDayCollectionWriter::writeToString() const
{
    using namespace pugi;
    xml_document doc;
    xml_node coll = doc.append_child("WorkDayCollection");

    for (size_t i(0); i < _workDays.size(); ++i)
    {
        WorkDay d = _workDays[i];
        xml_node day = coll.append_child("WorkDay");
        xml_node date = day.append_child("Date");
        date.append_child(xml_node_type::node_pcdata).set_value(d.getTime().toString().c_str());
        xml_node xPeriods = day.append_child("WorkPeriods");

        std::vector<GeneralWorkPeriod> periods = d.getWorkPeriods();
        for (size_t j(0); j < periods.size(); ++j)
        {
            xml_node xGP = xPeriods.append_child("GeneralWorkPeriod");
            xGP.append_child("Start").append_child(xml_node_type::node_pcdata).set_value(DateTime::toString(periods[j].getStart()).c_str());
            xGP.append_child("End").append_child(xml_node_type::node_pcdata).set_value(DateTime::toString(periods[j].getEnd()).c_str());
        }

        xml_node xJournalEntries = day.append_child("JournalEntries");
        std::vector<JournalEntry> journalEntries = d.getJournalEntries();
        for (size_t j(0); j < journalEntries.size(); ++j)
        {
            xml_node xJN = xJournalEntries.append_child("JournalEntry");
            xJN.append_child(xml_node_type::node_pcdata).set_value(journalEntries[j].getValue().c_str());
        }
    }

    xml_string_writer writer;
    doc.save(writer);

    return writer.result;
}

