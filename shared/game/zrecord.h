#pragma once

#include <vector>
#include <string>

class iresource;

class zrecord
{
public:
    zrecord(iresource& resource);

    std::vector<std::string> get_record_text() const;

    void process(const std::string& player, int value);

    std::string get_hero_name();

private:
    void parse(const std::vector<std::string>& record);
    void build_text_records();

private:
    iresource& m_resource;
    std::vector< std::pair<std::string, int> > m_records;
    std::vector<std::string> m_text_records;
};
